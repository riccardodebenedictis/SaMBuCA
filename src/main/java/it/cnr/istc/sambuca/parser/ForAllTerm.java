package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ForAllTerm implements Term {

    private final List<Variable> variables;
    private final Term formula;

    public ForAllTerm(Variable[] variables, Term formula) {
        assert Stream.of(variables).noneMatch(Objects::isNull);
        assert formula != null;
        this.variables = Arrays.asList(variables);
        this.formula = formula;
    }

    @Override
    public Term negate() {
        return new ExistsTerm(variables.stream().toArray(Variable[]::new), formula.negate());
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return formula.updatesPredicate(predicate);
    }

    @Override
    public boolean updatesFunction(Function function) {
        return formula.updatesFunction(function);
    }

    @Override
    public String toString() {
        return "(forall "
                + variables.stream().map(variable -> variable.getName() + " - " + variable.getType().getName())
                        .collect(Collectors.joining(" "))
                + " " + formula + ")";
    }
}
