package it.cnr.istc.sambuca.parser;

public class Constant {

    private final String name;
    private final Type type;

    Constant(String name, Type type) {
        assert type != null;
        this.name = name;
        this.type = type;
    }

    public String getName() {
        return name;
    }

    public Type getType() {
        return type;
    }

    @Override
    public String toString() {
        return type.getName() + " " + name;
    }
}
