package it.cnr.istc.sambuca.parser;

import java.math.BigDecimal;

public class HoldDuringTerm implements Term {

    private final BigDecimal start;
    private final BigDecimal end;
    private final Term term;

    public HoldDuringTerm(BigDecimal start, BigDecimal end, Term term) {
        this.start = start;
        this.end = end;
        this.term = term;
    }

    public BigDecimal getStart() {
        return start;
    }

    public BigDecimal getEnd() {
        return end;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a hold during term..");
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
        return "(hold-during " + start + " " + end + " " + term + ')';
    }
}
