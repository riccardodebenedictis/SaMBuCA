package it.cnr.istc.sambuca.parser;

public class AtEndTerm implements Term {

    private final Term term;

    public AtEndTerm(Term term) {
        this.term = term;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on an at end term..");
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
        return "(at end " + term + ')';
    }
}
