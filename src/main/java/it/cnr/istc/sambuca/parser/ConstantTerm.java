package it.cnr.istc.sambuca.parser;

public class ConstantTerm implements Term {

    private final Constant constant;

    public ConstantTerm(Constant constant) {
        assert constant != null;
        this.constant = constant;
    }

    public Constant getConstant() {
        return constant;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a constant..");
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
        return constant.getName();
    }
}
