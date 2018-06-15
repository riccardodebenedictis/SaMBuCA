package it.cnr.istc.sambuca.parser;

public class OverAllTerm implements Term {

    private final Term term;

    public OverAllTerm(Term term) {
        this.term = term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on an over all term..");
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
        return "(over all " + term + ')';
    }
}
