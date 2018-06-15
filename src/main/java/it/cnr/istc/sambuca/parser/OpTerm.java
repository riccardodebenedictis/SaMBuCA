package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class OpTerm implements Term {

    private final Op op;
    private final List<Term> terms;

    public OpTerm(Op op, Term... terms) {
        assert op != null;
        assert Stream.of(terms).noneMatch(Objects::isNull);
        this.op = op;
        this.terms = Arrays.asList(terms);
    }

    @Override
    public Term negate() {
        return new MinusTerm(new OpTerm(op, terms.stream().toArray(Term[]::new)));
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return false;
    }

    @Override
    public boolean updatesFunction(Function function) {
        return terms.stream().anyMatch(term -> term.updatesFunction(function));
    }

    @Override
    public String toString() {
        switch (op) {
        case Add:
            return "(+ " + terms.stream().map(term -> term.toString()).collect(Collectors.joining(" ")) + ")";
        case Sub:
            return "(- " + terms.stream().map(term -> term.toString()).collect(Collectors.joining(" ")) + ")";
        case Mul:
            return "(* " + terms.stream().map(term -> term.toString()).collect(Collectors.joining(" ")) + ")";
        case Div:
            return "(/ " + terms.stream().map(term -> term.toString()).collect(Collectors.joining(" ")) + ")";
        default:
            throw new AssertionError(op.name());
        }
    }

    public enum Op {
        Add, Sub, Mul, Div
    }
}
