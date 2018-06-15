package it.cnr.istc.sambuca.parser;

import java.math.BigDecimal;

public class HoldAfterTerm implements Term {

    private final BigDecimal after;
    private final Term term;

    public HoldAfterTerm(BigDecimal after, Term term) {
        this.after = after;
        this.term = term;
    }

    public BigDecimal getAfter() {
        return after;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a hold after term..");
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
        return "(hold-after " + after + " " + term + ')';
    }
}
