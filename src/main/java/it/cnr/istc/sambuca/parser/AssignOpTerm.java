package it.cnr.istc.sambuca.parser;

public class AssignOpTerm implements Term {

    private final AssignOp assignOp;
    private final FunctionTerm functionTerm;
    private final Term value;

    public AssignOpTerm(AssignOp assignOp, FunctionTerm functionTerm, Term value) {
        this.assignOp = assignOp;
        this.functionTerm = functionTerm;
        this.value = value;
    }

    public AssignOp getAssignOp() {
        return assignOp;
    }

    public FunctionTerm getFunctionTerm() {
        return functionTerm;
    }

    public Term getValue() {
        return value;
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on an assignment term..");
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return false;
    }

    @Override
    public boolean updatesFunction(Function function) {
        return functionTerm.updatesFunction(function) || value.updatesFunction(function);
    }

    @Override
    public String toString() {
        switch (assignOp) {
        case Assign:
            return "(assign " + functionTerm + " " + value + ")";
        case ScaleUp:
            return "(scale-up " + functionTerm + " " + value + ")";
        case ScaleDown:
            return "(scale-down " + functionTerm + " " + value + ")";
        case Increase:
            return "(increase " + functionTerm + " " + value + ")";
        case Decrease:
            return "(decrease " + functionTerm + " " + value + ")";
        default:
            throw new AssertionError(assignOp.name());
        }
    }

    public enum AssignOp {
        Assign, ScaleUp, ScaleDown, Increase, Decrease
    }
}
