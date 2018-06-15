package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class OrTerm implements Term {

    private final List<Term> terms;

    public OrTerm(Term... terms) {
        assert Stream.of(terms).noneMatch(Objects::isNull);
        this.terms = Arrays.asList(terms);
    }

    public List<Term> getTerms() {
        return Collections.unmodifiableList(terms);
    }

    @Override
    public Term negate() {
        return new AndTerm(terms.stream().map(term -> term.negate()).toArray(Term[]::new));
    }

    @Override
    public boolean updatesPredicate(Predicate predicate) {
        return terms.stream().anyMatch(term -> term.updatesPredicate(predicate));
    }

    @Override
    public boolean updatesFunction(Function function) {
        return terms.stream().anyMatch(term -> term.updatesFunction(function));
    }

    @Override
    public String toString() {
        return "(or " + terms.stream().map(term -> term.toString()).collect(Collectors.joining(" ")) + ")";
    }
}
