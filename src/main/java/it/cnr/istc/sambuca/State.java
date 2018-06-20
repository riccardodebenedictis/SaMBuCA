package it.cnr.istc.sambuca;

import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.IdentityHashMap;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

import it.cnr.istc.sambuca.parser.Action;
import it.cnr.istc.sambuca.parser.AndTerm;
import it.cnr.istc.sambuca.parser.Constant;
import it.cnr.istc.sambuca.parser.ConstantTerm;
import it.cnr.istc.sambuca.parser.OrTerm;
import it.cnr.istc.sambuca.parser.PredicateTerm;
import it.cnr.istc.sambuca.parser.Term;
import it.cnr.istc.sambuca.parser.Variable;
import it.cnr.istc.sambuca.parser.VariableTerm;

/**
 * State
 */
public class State {

    private final GAction a; // the (ground) action which led to this state..
    private final Set<String> atoms; // these are those atoms which are true in the current state..

    public State(GAction a, Collection<String> atms) {
        this.a = a;
        this.atoms = new HashSet<>(atms);
    }

    /**
     * Returns the action which led to this state.
     * 
     * @return the action which led to this state.
     */
    public GAction getAction() {
        return a;
    }

    public boolean contains(String atom) {
        return atoms.contains(atom);
    }

    /**
     * Checks whether the given action is applicable in the current state within the
     * given assignment of constants to the variables.
     * 
     * @param a the (ground) action we are checking for applicability.
     * @return a boolean representin whether the given action is applicable in the
     *         current state.
     */
    public boolean isApplicable(GAction a) {
        return isSatisfied(a.a.getPrecondition(), a.assgnmnt);
    }

    /**
     * Checks whether the given term is satisfied in the current state within the
     * given assignment of constants to the variables.
     * 
     * @param t        the term we are checking whether it is satisfied.
     * @param assgnmnt an assignment of constants to a set of variables.
     * @return a boolean representin whether the given term is satisfied in the
     *         current state.
     */
    public boolean isSatisfied(Term t, Map<Variable, Constant> assgnmnt) {
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
            return pt.isDirected() ? atoms.contains(trm) : !atoms.contains(trm);
        } else if (t instanceof AndTerm)
            return ((AndTerm) t).getTerms().stream().allMatch(c_t -> isSatisfied(c_t, assgnmnt));
        else if (t instanceof OrTerm)
            return ((OrTerm) t).getTerms().stream().anyMatch(c_t -> isSatisfied(c_t, assgnmnt));
        else
            throw new UnsupportedOperationException("Not supported yet.. " + t.getClass().getName());
    }

    /**
     * Applies the given action, with the given assignment of constants to its
     * variables, to this state, returning a new state representing the state
     * resulting from the application of the action to this state.
     * 
     * @param a the (ground) action action applied to this state.
     * @return the state resulting from the application of the action to this state.
     */
    public State applyAction(GAction a) {
        return new State(a, applyTerm(a.a.getEffect(), a.assgnmnt, new HashSet<>(atoms)));
    }

    private Set<String> applyTerm(Term t, Map<Variable, Constant> assgnmnt, Set<String> resulting_state) {
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
            ((AndTerm) t).getTerms().stream().forEach(trm -> applyTerm(trm, assgnmnt, resulting_state));
        else
            throw new UnsupportedOperationException("Not supported yet.. " + t.getClass().getName());
        return resulting_state;
    }

    public static class GAction {

        private final Action a;
        private final Map<Variable, Constant> assgnmnt;

        GAction(Action a, Map<Variable, Constant> assgnmnt) {
            this.a = a;
            this.assgnmnt = assgnmnt;
        }
    }
}