package it.cnr.istc.sambuca.parser;

public class SometimeAfterTerm implements Term {

    private final Term firstTerm;
    private final Term secondTerm;

    public SometimeAfterTerm(Term firstTerm, Term secondTerm) {
        this.firstTerm = firstTerm;
        this.secondTerm = secondTerm;
    }

    public Term getFirstTerm() {
        return firstTerm;
    }

    public Term getSecondTerm() {
        return secondTerm;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a sometime after term..");
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
        return "(sometime-after " + " " + firstTerm + " " + secondTerm + ')';
    }
}
