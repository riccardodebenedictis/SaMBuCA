package it.cnr.istc.sambuca.parser;

public class ComparisonTerm implements Term {

    private final Comp comp;
    private final Term firstTerm, secondTerm;

    public ComparisonTerm(Comp comp, Term firstTerm, Term secondTerm) {
        assert comp != null;
        assert firstTerm != null;
        assert secondTerm != null;
        this.comp = comp;
        this.firstTerm = firstTerm;
        this.secondTerm = secondTerm;
    }

    @Override
    public Term negate() {
        switch (comp) {
        case Gt:
            return new ComparisonTerm(Comp.LEq, firstTerm, secondTerm);
        case Lt:
            return new ComparisonTerm(Comp.GEq, firstTerm, secondTerm);
        case Eq:
            return new OrTerm(firstTerm.negate(), secondTerm);
        case GEq:
            return new ComparisonTerm(Comp.Lt, firstTerm, secondTerm);
        case LEq:
            return new ComparisonTerm(Comp.Gt, firstTerm, secondTerm);
        default:
            throw new AssertionError(comp.name());
        }
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
        switch (comp) {
        case Gt:
            return "(> " + firstTerm + " " + secondTerm + ")";
        case Lt:
            return "(< " + firstTerm + " " + secondTerm + ")";
        case Eq:
            return "(= " + firstTerm + " " + secondTerm + ")";
        case GEq:
            return "(>= " + firstTerm + " " + secondTerm + ")";
        case LEq:
            return "(<= " + firstTerm + " " + secondTerm + ")";
        default:
            throw new AssertionError(comp.name());
        }
    }

    public enum Comp {
        Gt, Lt, Eq, GEq, LEq;
    }
}
