package it.cnr.istc.sambuca.parser;

public class ProblemInstance {

    private final Domain domain;
    private final Problem problem;

    public ProblemInstance(Domain domain, Problem problem) {
        this.domain = domain;
        this.problem = problem;
    }

    public Domain getDomain() {
        return domain;
    }

    public Problem getProblem() {
        return problem;
    }
}