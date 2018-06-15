package it.cnr.istc.sambuca.parser;

import java.math.BigDecimal;

public class WithinTerm implements Term {

    private final BigDecimal within;
    private final Term term;

    public WithinTerm(BigDecimal within, Term term) {
        this.within = within;
        this.term = term;
    }

    public BigDecimal getWithin() {
        return within;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a within term..");
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
        return "(within " + within + " " + term + ')';
    }
}
