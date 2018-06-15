package it.cnr.istc.sambuca.parser;

import java.math.BigDecimal;

public class NumberTerm implements Term {

    private final BigDecimal value;

    public NumberTerm(BigDecimal value) {
        this.value = value;
    }

    public BigDecimal getValue() {
        return value;
    }

    @Override
    public Term negate() {
        return new NumberTerm(value.negate());
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
        return value.toString();
    }
}
