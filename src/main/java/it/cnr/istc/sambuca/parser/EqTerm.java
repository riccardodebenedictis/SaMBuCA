package it.cnr.istc.sambuca.parser;

public class EqTerm implements Term {

    private final boolean directed;
    private final Term firstTerm, secondTerm;

    public EqTerm(boolean directed, Term firstTerm, Term secondTerm) {
        assert firstTerm != null;
        assert secondTerm != null;
        this.directed = directed;
        this.firstTerm = firstTerm;
        this.secondTerm = secondTerm;
    }

    public boolean isDirected() {
        return directed;
    }

    public Term getFirstTerm() {
        return firstTerm;
    }

    public Term getSecondTerm() {
        return secondTerm;
    }

    @Override
    public Term negate() {
        return new EqTerm(!directed, firstTerm, secondTerm);
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return firstTerm.updatesPredicate(predicate) || secondTerm.updatesPredicate(predicate);
    }

    @Override
    public boolean updatesFunction(Function function) {
        return firstTerm.updatesFunction(function) || secondTerm.updatesFunction(function);
    }

    @Override
    public String toString() {
        if (directed) {
            return "(= " + firstTerm + " " + secondTerm + ")";
        } else {
            return "(not (= " + firstTerm + " " + secondTerm + "))";
        }
    }
}
