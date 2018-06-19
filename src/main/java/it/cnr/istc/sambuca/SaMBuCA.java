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

    private final ProblemInstance pi;
    private final Network nn;

    public SaMBuCA(String domain_path, String problem_path) throws IOException {
        this.pi = PDDLLanguageParser.parse(domain_path, problem_path);

        // this is the list of all the ground predicates..
        List<String> ground_preds = new ArrayList<>();
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

        // this is the list of all the (ground) action..
        List<GAction> actions = new ArrayList<>();
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
    }

    private static boolean isSatisfied(Set<String> state, Term t, Map<Variable, Constant> assgnmnt) {
        if (t instanceof PredicateTerm) {
            PredicateTerm pt = (PredicateTerm) t;
            String trm = "(" + pt.getPredicate().getName() + (pt.getArguments().isEmpty() ? "" : " ")
                    + pt.getArguments().stream().map(arg -> {
                        if (arg instanceof VariableTerm)
                            return assgnmnt.get(((VariableTerm) arg).getVariable()).toString();
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
                            return assgnmnt.get(((VariableTerm) arg).getVariable()).toString();
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