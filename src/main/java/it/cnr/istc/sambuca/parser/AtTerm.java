package it.cnr.istc.sambuca.parser;

import java.math.BigDecimal;

public class AtTerm implements Term {

    private final BigDecimal at;
    private final PredicateTerm predicateTerm;

    public AtTerm(BigDecimal at, PredicateTerm predicateTerm) {
        assert at != null;
        assert predicateTerm != null;
        this.at = at;
        this.predicateTerm = predicateTerm;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on an at term..");
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return predicateTerm.updatesPredicate(predicate);
    }

    @Override
    public boolean updatesFunction(Function function) {
        return false;
    }

    @Override
    public String toString() {
        return "(at " + at + " " + predicateTerm + ")";
    }
}
