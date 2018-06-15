package it.cnr.istc.sambuca.parser;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Function {

    private final String name;
    private final Type type;
    private final List<Variable> variables;

    public Function(String name, Type type, Variable... variables) {
        assert Stream.of(variables).noneMatch(Objects::isNull);
        assert type != null;
        this.name = name;
        this.type = type;
        this.variables = Arrays.asList(variables);
    }

    public String getName() {
        return name;
    }

    public Type getType() {
        return type;
    }

    public List<Variable> getVariables() {
        return Collections.unmodifiableList(variables);
    }

    @Override
    public String toString() {
        return "(" + name + " "
                + variables.stream().map(variable -> variable.getName() + " - " + variable.getType().getName())
                        .collect(Collectors.joining(" "))
                + ") - " + type.getName();
    }
}
