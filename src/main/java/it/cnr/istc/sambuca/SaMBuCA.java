package it.cnr.istc.sambuca;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import it.cnr.istc.neon.Network;
import it.cnr.istc.neon.activation.Sigmoid;
import it.cnr.istc.neon.error.CrossEntropy;
import it.cnr.istc.sambuca.parser.Action;
import it.cnr.istc.sambuca.parser.AndTerm;
import it.cnr.istc.sambuca.parser.Constant;
import it.cnr.istc.sambuca.parser.ConstantTerm;
import it.cnr.istc.sambuca.parser.OrTerm;
import it.cnr.istc.sambuca.parser.PDDLLanguageParser;
import it.cnr.istc.sambuca.parser.Predicate;
import it.cnr.istc.sambuca.parser.PredicateTerm;
import it.cnr.istc.sambuca.parser.ProblemInstance;
import it.cnr.istc.sambuca.parser.Term;
import it.cnr.istc.sambuca.parser.Variable;
import it.cnr.istc.sambuca.parser.VariableTerm;

/**
 * SaMBuCA
 */
public class SaMBuCA {

    private final ProblemInstance pi; // the PDDL problem instance..
    private final List<String> ground_preds = new ArrayList<>(); // the list of all the ground predicates..
    private final List<GAction> actions = new ArrayList<>(); // the list of all the (ground) action..
    private final Network nn; // the artificial neural network..

    public SaMBuCA(String domain_path, String problem_path) throws IOException {
        this.pi = PDDLLanguageParser.parse(domain_path, problem_path);

        // we fill the list of all the ground predicates..
        for (Predicate p : pi.getDomain().getPredicates().values()) {
            List<Variable> vars = p.getVariables();
            if (vars.isEmpty())
                ground_preds.add("(" + p.getName() + ")");
            else {
                Constant[][] cnsts = new Constant[vars.size()][];
                for (int i = 0; i < vars.size(); i++)
                    cnsts[i] = vars.get(i).getType().getInstances()
                            .toArray(new Constant[vars.get(i).getType().getInstances().size()]);
                for (Constant[] cs : new CartesianProductGenerator<>(cnsts))
                    ground_preds.add("(" + p.getName() + " "
                            + Stream.of(cs).map(argument -> argument.toString()).collect(Collectors.joining(" "))
                            + ")");
            }
        }

        // we fill the list of all the (ground) action..
        for (Action a : pi.getDomain().getActions().values()) {
            List<Variable> vars = a.getVariables();
            if (vars.isEmpty())
                actions.add(new GAction(a, Collections.emptyMap()));
            else {
                Constant[][] cnsts = new Constant[vars.size()][];
                for (int i = 0; i < vars.size(); i++)
                    cnsts[i] = vars.get(i).getType().getInstances()
                            .toArray(new Constant[vars.get(i).getType().getInstances().size()]);
                for (Constant[] cs : new CartesianProductGenerator<>(cnsts)) {
                    Map<Variable, Constant> assgnmnt = new HashMap<>(cs.length);
                    for (int i = 0; i < vars.size(); i++)
                        assgnmnt.put(vars.get(i), cs[i]);
                    actions.add(new GAction(a, assgnmnt));
                }
            }
        }

        // this is the initial state..
        Set<String> init = new HashSet<>();
        for (Term t : pi.getProblem().getInitEls()) {
            init.add(t.toString());
        }

        // we create the neural network..
        this.nn = new Network(new CrossEntropy(), new Sigmoid(), ground_preds.size() * 2, ground_preds.size(),
                ground_preds.size(), 1);

        // we compute the best action according to the current neural network..
        GAction best_action = getBestAction(init);
    }

    private static boolean isSatisfied(Set<String> state, Term t, Map<Variable, Constant> assgnmnt) {
        if (t instanceof PredicateTerm) {
            PredicateTerm pt = (PredicateTerm) t;
            String trm = "(" + pt.getPredicate().getName() + (pt.getArguments().isEmpty() ? "" : " ")
                    + pt.getArguments().stream().map(arg -> {
                        if (arg instanceof VariableTerm)
                            return assgnmnt.get(((VariableTerm) arg).getVariable()).getName();
                        else if (arg instanceof ConstantTerm)
                            return arg.toString();
                        else
                            throw new UnsupportedOperationException("Not supported yet.. " + arg.getClass().getName());
                    }).collect(Collectors.joining(" ")) + ")";
            return pt.isDirected() ? state.contains(trm) : !state.contains(trm);
        } else if (t instanceof AndTerm)
            return ((AndTerm) t).getTerms().stream().allMatch(c_t -> isSatisfied(state, c_t, assgnmnt));
        else if (t instanceof OrTerm)
            return ((OrTerm) t).getTerms().stream().anyMatch(c_t -> isSatisfied(state, c_t, assgnmnt));
        else
            throw new UnsupportedOperationException("Not supported yet.. " + t.getClass().getName());
    }

    private static Set<String> applyTerm(Set<String> state, Term t, Map<Variable, Constant> assgnmnt,
            Set<String> resulting_state) {
        if (t instanceof PredicateTerm) {
            PredicateTerm pt = (PredicateTerm) t;
            String trm = "(" + pt.getPredicate().getName() + (pt.getArguments().isEmpty() ? "" : " ")
                    + pt.getArguments().stream().map(arg -> {
                        if (arg instanceof VariableTerm)
                            return assgnmnt.get(((VariableTerm) arg).getVariable()).getName();
                        else if (arg instanceof ConstantTerm)
                            return arg.toString();
                        else
                            throw new UnsupportedOperationException("Not supported yet.. " + arg.getClass().getName());
                    }).collect(Collectors.joining(" ")) + ")";
            if (pt.isDirected())
                resulting_state.add(trm);
            else
                resulting_state.remove(trm);
        } else if (t instanceof AndTerm)
            ((AndTerm) t).getTerms().stream().forEach(trm -> applyTerm(state, trm, assgnmnt, resulting_state));
        else
            throw new UnsupportedOperationException("Not supported yet.. " + t.getClass().getName());
        return resulting_state;
    }

    private GAction getBestAction(Set<String> state) {
        GAction best_action = null;
        double best_q = Double.NEGATIVE_INFINITY;
        for (GAction a : actions) {
            if (a.isApplicable(state)) {
                Set<String> resulting_state = a.apply(state);
                double[] d_state = new double[ground_preds.size()];
                for (int i = 0; i < d_state.length; i++) {
                    d_state[i] = resulting_state.contains(ground_preds.get(i)) ? 1 : 0;
                }
                double eval = nn.forward(d_state)[0];
                if (eval > best_q) {
                    best_action = a;
                    best_q = eval;
                }
            }
        }
        return best_action;
    }

    private static class GAction {

        private final Action a;
        private final Map<Variable, Constant> assgnmnt;

        private GAction(Action a, Map<Variable, Constant> assgnmnt) {
            this.a = a;
            this.assgnmnt = assgnmnt;
        }

        private boolean isApplicable(Set<String> state) {
            return isSatisfied(state, a.getPrecondition(), Collections.unmodifiableMap(assgnmnt));
        }

        private Set<String> apply(Set<String> state) {
            return applyTerm(state, a.getEffect(), assgnmnt, new HashSet<>(state));
        }
    }
}