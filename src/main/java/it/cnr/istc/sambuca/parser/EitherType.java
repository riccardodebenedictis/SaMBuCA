package it.cnr.istc.sambuca.parser;

import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

public class EitherType extends Type {

    private final List<Type> types;

    public EitherType(List<Type> types) {
        super("Either" + types.stream().map(type -> type.getName()).collect(Collectors.joining()));
        this.types = types;
    }

    @Override
    public Collection<Constant> getInstances() {
        return types.stream().flatMap(type -> type.getInstances().stream()).distinct().collect(Collectors.toList());
    }

    @Override
    public String toString() {
        return "(either " + types.stream().map(type -> type.getName()).collect(Collectors.joining(" ")) + ")";
    }
}
