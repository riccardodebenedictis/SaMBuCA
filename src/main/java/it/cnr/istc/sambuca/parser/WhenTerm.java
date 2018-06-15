package it.cnr.istc.sambuca.parser;

public class WhenTerm implements Term {

    private final Term condition;
    private final Term effect;

    public WhenTerm(Term condition, Term effect) {
        assert condition != null;
        assert effect != null;
        this.condition = condition;
        this.effect = effect;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a conditiona effect..");
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return effect.updatesPredicate(predicate);
    }

    @Override
    public boolean updatesFunction(Function function) {
        return effect.updatesFunction(function);
    }

    @Override
    public String toString() {
        return "(when " + condition + " " + effect + ")";
    }
}
