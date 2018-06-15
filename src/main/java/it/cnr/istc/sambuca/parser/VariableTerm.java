package it.cnr.istc.sambuca.parser;

public class VariableTerm implements Term {

    private final Variable variable;

    public VariableTerm(Variable variable) {
        assert variable != null;
        this.variable = variable;
    }

    public Variable getVariable() {
        return variable;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a variable..");
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
        return variable.getName();
    }
}
