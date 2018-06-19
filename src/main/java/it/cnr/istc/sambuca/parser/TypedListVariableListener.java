package it.cnr.istc.sambuca.parser;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

class TypedListVariableListener extends PDDLBaseListener {

    private final Domain domain;
    final List<Variable> variables = new ArrayList<>();

    TypedListVariableListener(Domain domain) {
        this.domain = domain;
    }

    @Override
    public void enterTyped_list_variable(PDDLParser.Typed_list_variableContext ctx) {
        Type type = null;
        if (ctx.type() == null) {
            type = Type.OBJECT;
        } else if (ctx.type().primitive_type().size() == 1) {
            type = ctx.type().primitive_type(0).name() == null ? Type.OBJECT
                    : domain.getType(ctx.type().primitive_type(0).name().getText().toLowerCase());
        } else {
            type = new EitherType(ctx.type().primitive_type().stream()
                    .map(primitive_type -> primitive_type.name() == null ? Type.OBJECT
                            : domain.getType(primitive_type.name().getText().toLowerCase()))
                    .collect(Collectors.toList()));
            if (!domain.getTypes().containsKey(type.getName())) {
                domain.addType(type);
            }
        }

        assert type != null : "Cannot find type " + ctx.type().primitive_type(0).name().getText().toLowerCase();
        Type c_type = type;
        ctx.variable().stream().forEach(variable -> {
            variables.add(new Variable("?" + variable.name().getText().toLowerCase(), c_type));
        });
    }
}