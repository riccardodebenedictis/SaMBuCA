package it.cnr.istc.sambuca.parser;

import java.math.BigDecimal;

public class AlwaysWithinTerm implements Term {

    private final BigDecimal within;
    private final Term firstTerm;
    private final Term secondTerm;

    public AlwaysWithinTerm(BigDecimal within, Term firstTerm, Term secondTerm) {
        this.within = within;
        this.firstTerm = firstTerm;
        this.secondTerm = secondTerm;
    }

    public BigDecimal getWithin() {
        return within;
    }

    public Term getFirstTerm() {
        return firstTerm;
    }

    public Term getSecondTerm() {
        return secondTerm;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on an always within term..");
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
        return "(always-within " + within + " " + firstTerm + " " + secondTerm + ')';
    }
}
