package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class PredicateTerm implements Term {

    private final boolean directed;
    private final Predicate predicate;
    private final List<Term> arguments;

    public PredicateTerm(boolean directed, Predicate predicate, Term... arguments) {
        assert predicate != null;
        assert Stream.of(arguments).noneMatch(Objects::isNull);
        this.directed = directed;
        this.predicate = predicate;
        this.arguments = Arrays.asList(arguments);
    }

    public boolean isDirected() {
        return directed;
    }

    public Predicate getPredicate() {
        return predicate;
    }

    public List<Term> getArguments() {
        return Collections.unmodifiableList(arguments);
    }

    @Override
    public Term negate() {
        return new PredicateTerm(!directed, predicate, arguments.stream().toArray(Term[]::new));
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return this.predicate == predicate;
    }

    @Override
    public boolean updatesFunction(Function function) {
        return false;
    }

    @Override
    public String toString() {
        if (directed) {
            return "(" + predicate.getName() + (arguments.isEmpty() ? "" : " ")
                    + arguments.stream().map(argument -> argument.toString()).collect(Collectors.joining(" ")) + ")";
        } else {
            return "(not (" + predicate.getName() + (arguments.isEmpty() ? "" : " ")
                    + arguments.stream().map(argument -> argument.toString()).collect(Collectors.joining(" ")) + "))";
        }
    }
}
