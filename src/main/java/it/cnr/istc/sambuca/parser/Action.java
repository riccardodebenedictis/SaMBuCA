package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Action {

    private final String name;
    private final List<Variable> variables;
    private Term precondition;
    private Term effect;

    public Action(String name, Variable... variables) {
        assert Stream.of(variables).noneMatch(Objects::isNull);
        this.name = name;
        this.variables = Arrays.asList(variables);
    }

    public String getName() {
        return name;
    }

    public List<Variable> getVariables() {
        return Collections.unmodifiableList(variables);
    }

    public Term getPrecondition() {
        return precondition;
    }

    public void setPrecondition(Term precondition) {
        assert precondition != null;
        this.precondition = precondition;
    }

    public Term getEffect() {
        return effect;
    }

    public void setEffect(Term effect) {
        assert effect != null;
        this.effect = effect;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("(action ").append(name).append(" (")
                .append(variables.stream().map(variable -> variable.getName() + " - " + variable.getType().getName())
                        .collect(Collectors.joining(" ")))
                .append(")\n");
        if (precondition != null) {
            sb.append("(:precondition ").append(precondition.toString()).append(")\n");
        }
        if (effect != null) {
            sb.append("(:effect ").append(effect.toString()).append(")\n");
        }
        sb.append(")");
        return sb.toString();
    }
}
