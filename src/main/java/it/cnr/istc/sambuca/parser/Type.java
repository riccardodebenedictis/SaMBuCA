package it.cnr.istc.sambuca.parser;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

public class Type {

    public static final Type OBJECT = new Type("Object");
    public static final Type NUMBER = new Type("number");
    private final String name;
    private Type superclass;
    private final Collection<Constant> instances = new ArrayList<>();

    public Type(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public Type getSuperclass() {
        return superclass;
    }

    public void setSuperclass(Type superclass) {
        this.superclass = superclass;
    }

    public Constant newInstance(String name) {
        Constant instance = new Constant(name, this);
        addInstance(instance);
        return instance;
    }

    private void addInstance(Constant instance) {
        instances.add(instance);
        if (superclass != null) {
            superclass.addInstance(instance);
        }
    }

    public Collection<Constant> getInstances() {
        return Collections.unmodifiableCollection(instances);
    }

    @Override
    public String toString() {
        return name + (superclass != null ? " - " + superclass.name : "");
    }
}
