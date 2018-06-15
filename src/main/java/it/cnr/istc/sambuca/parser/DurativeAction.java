package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class DurativeAction {

    private final String name;
    private final List<Variable> variables;
    private Term duration;
    private Term condition;
    private Term effect;

    public DurativeAction(String name, Variable... variables) {
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

    public Term getDuration() {
        return duration;
    }

    public void setDuration(Term duration) {
        assert duration != null;
        this.duration = duration;
    }

    public Term getCondition() {
        return condition;
    }

    public void setCondition(Term condition) {
        assert condition != null;
        this.condition = condition;
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
        sb.append("(durative-action ").append(name).append("( ")
                .append(variables.stream().map(variable -> variable.getName() + " - " + variable.getType().getName())
                        .collect(Collectors.joining(" ")))
                .append(")\n");
        if (duration != null) {
            sb.append("(:duration ").append(duration.toString()).append(")\n");
        }
        if (condition != null) {
            sb.append("(:condition ").append(condition.toString()).append(")\n");
        }
        if (effect != null) {
            sb.append("(:effect ").append(effect.toString()).append(")\n");
        }
        sb.append(")");
        return sb.toString();
    }
}
