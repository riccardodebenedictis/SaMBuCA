package it.cnr.istc.sambuca.parser;

public class AtStartTerm implements Term {

    private final Term term;

    public AtStartTerm(Term term) {
        this.term = term;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on an at start term..");
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return term.updatesPredicate(predicate);
    }

    @Override
    public boolean updatesFunction(Function function) {
        return term.updatesFunction(function);
    }

    @Override
    public String toString() {
        return "(at start " + term + ')';
    }
}
