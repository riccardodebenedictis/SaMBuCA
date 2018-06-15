package it.cnr.istc.sambuca.parser;

public class SometimeTerm implements Term {

    private final Term term;

    public SometimeTerm(Term term) {
        this.term = term;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a sometime term..");
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return false;
    }

    @Override
    public boolean updatesFunction(Function function) {
        return false;
    }

    @Override
    public String toString() {
        return "(sometime " + term + ')';
    }
}
