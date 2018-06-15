package it.cnr.istc.sambuca.parser;

public class PreferenceTerm implements Term {

    private final String name;
    private final Term term;

    public PreferenceTerm(String name, Term term) {
        this.name = name;
        this.term = term;
    }

    public String getName() {
        return name;
    }

    public Term getTerm() {
        return term;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a preference term..");
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
        if (name != null) {
            return "(preference " + name + " " + term + ')';
        } else {
            return "(preference " + term + ')';
        }
    }
}
