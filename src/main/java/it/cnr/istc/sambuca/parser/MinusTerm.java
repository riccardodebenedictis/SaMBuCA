package it.cnr.istc.sambuca.parser;

public class MinusTerm implements Term {

    private final Term term;

    public MinusTerm(Term term) {
        this.term = term;
    }

    @Override
    public Term negate() {
        return term;
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
        return "(- " + term + ")";
    }
}
