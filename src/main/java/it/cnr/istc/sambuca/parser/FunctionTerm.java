package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class FunctionTerm implements Term {

    private final Function function;
    private final List<Term> arguments;

    public FunctionTerm(Function function, Term... arguments) {
        assert function != null;
        assert Stream.of(arguments).noneMatch(Objects::isNull);
        this.function = function;
        this.arguments = Arrays.asList(arguments);
    }

    public Function getFunction() {
        return function;
    }

    public List<Term> getArguments() {
        return Collections.unmodifiableList(arguments);
    }

    @Override
    public Term negate() {
        throw new AssertionError("It is not possible to call negate on a function..");
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return false;
    }

    @Override
    public boolean updatesFunction(Function function) {
        return this.function == function;
    }

    @Override
    public String toString() {
        return "(" + function.getName() + " "
                + arguments.stream().map(argument -> argument.toString()).collect(Collectors.joining(" ")) + ")";
    }
}
