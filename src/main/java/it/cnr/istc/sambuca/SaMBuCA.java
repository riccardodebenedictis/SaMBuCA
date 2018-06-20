package it.cnr.istc.sambuca;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import it.cnr.istc.neon.Network;
import it.cnr.istc.neon.activation.Sigmoid;
import it.cnr.istc.neon.error.CrossEntropy;
import it.cnr.istc.sambuca.State.GAction;
import it.cnr.istc.sambuca.parser.Action;
import it.cnr.istc.sambuca.parser.AndTerm;
import it.cnr.istc.sambuca.parser.Constant;
import it.cnr.istc.sambuca.parser.ConstantTerm;
import it.cnr.istc.sambuca.parser.PDDLLanguageParser;
import it.cnr.istc.sambuca.parser.Predicate;
import it.cnr.istc.sambuca.parser.PredicateTerm;
import it.cnr.istc.sambuca.parser.ProblemInstance;
import it.cnr.istc.sambuca.parser.Term;
import it.cnr.istc.sambuca.parser.Variable;

/**
 * SaMBuCA
 */
public class SaMBuCA {

    private final ProblemInstance pi; // the PDDL problem instance..
    private final List<String> ground_preds = new ArrayList<>(); // the list of all the ground predicates..
    private final List<GAction> actions = new ArrayList<>(); // the list of all the (ground) actions..
    private final State init; // the initial state..
    private final double[] goals; // a neural network oriented representation of the current goals..
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
                            + Stream.of(cs).map(arg -> arg.getName()).collect(Collectors.joining(" ")) + ")");
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
        init = new State(null,
                pi.getProblem().getInitEls().stream().map(ie -> ie.toString()).collect(Collectors.toList()));

        // this is a representation of the goals..
        goals = new double[ground_preds.size()];
        Arrays.fill(goals, 0.5);
        setGoals(pi.getProblem().getGoal());

        // we create the neural network..
        this.nn = new Network(new CrossEntropy(), new Sigmoid(), ground_preds.size() * 2, ground_preds.size(),
                ground_preds.size(), 1);

        // we compute the best action according to the current neural network..
        GAction best_action = getBestAction(init);
    }

    private void setGoals(Term t) {
        if (t instanceof PredicateTerm) {
            PredicateTerm pt = (PredicateTerm) t;
            String trm = "(" + pt.getPredicate().getName() + (pt.getArguments().isEmpty() ? "" : " ")
                    + pt.getArguments().stream().map(arg -> {
                        if (arg instanceof ConstantTerm)
                            return arg.toString();
                        else
                            throw new UnsupportedOperationException("Not supported yet.. " + arg.getClass().getName());
                    }).collect(Collectors.joining(" ")) + ")";
            for (int i = 0; i < ground_preds.size(); i++) {
                if (ground_preds.get(i).equals(trm)) {
                    goals[i] = pt.isDirected() ? 1 : 0;
                    break;
                }
            }
        } else if (t instanceof AndTerm)
            ((AndTerm) t).getTerms().stream().forEach(trm -> setGoals(trm));
        else
            throw new UnsupportedOperationException("Not supported yet.. " + t.getClass().getName());
    }

    private GAction getBestAction(State state) {
        GAction best_action = null;
        double best_q = Double.NEGATIVE_INFINITY;
        for (GAction a : actions) {
            if (state.isApplicable(a)) {
                State resulting_state = state.applyAction(a);
                double[] d_state = new double[ground_preds.size()];
                for (int i = 0; i < d_state.length; i++) {
                    d_state[i] = resulting_state.contains(ground_preds.get(i)) ? 1 : 0;
                }
                double[] x = new double[ground_preds.size() * 2];
                System.arraycopy(d_state, 0, x, 0, d_state.length);
                System.arraycopy(goals, 0, x, d_state.length, goals.length);
                double eval = nn.forward(x)[0];
                if (eval > best_q) {
                    best_action = a;
                    best_q = eval;
                }
            }
        }
        return best_action;
    }
}