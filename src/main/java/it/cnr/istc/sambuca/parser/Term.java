package it.cnr.istc.sambuca.parser;

public interface Term {

    Term negate();

    boolean updatesPredicate(Predicate predicate);

    boolean updatesFunction(Function function);
}
