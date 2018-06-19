package it.cnr.istc.sambuca.parser;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class PDDLRequirements {

    private static final String REQUIREMENTS_EXPR;

    static {
        Requirement[] values = Requirement.values();
        StringBuilder regex = new StringBuilder();
        for (int i = 0; i < values.length; i++) {
            if (i > 0) {
                regex.append("|");
            }
            regex.append(values[i].name);
        }
        REQUIREMENTS_EXPR = regex.toString();
    }

    static Set<String> getRequirements(String pddl_path) throws IOException {
        Set<String> requirements = new HashSet<>();
        try (Scanner scanner = new Scanner(Paths.get(pddl_path)).skip(";*")) {
            String requirement = "";
            while (requirement != null) {
                requirement = scanner.findWithinHorizon(REQUIREMENTS_EXPR, 0);
                if (requirement != null) {
                    addRequirement(requirements, requirement);
                }
            }
            if (requirements.containsAll(Arrays.asList(Requirement.EXISTENTIAL_PRECONDITIONS.name,
                    Requirement.UNIVERSAL_PRECONDITIONS.name))) {
                addRequirement(requirements, Requirement.QUANTIFIED_PRECONDITIONS.name);
            }
            if (requirements
                    .containsAll(Arrays.asList(Requirement.NUMERIC_FLUENTS.name, Requirement.OBJECT_FLUENTS.name))) {
                addRequirement(requirements, Requirement.FLUENTS.name);
            }
            if (requirements.containsAll(Arrays.asList(Requirement.STRIPS.name, Requirement.TYPING.name,
                    Requirement.NEGATIVE_PRECONDITIONS.name, Requirement.DISJUNCTIVE_PRECONDITIONS.name,
                    Requirement.EQUALITY.name, Requirement.QUANTIFIED_PRECONDITIONS.name,
                    Requirement.CONDITIONAL_EFFECTS.name))) {
                addRequirement(requirements, Requirement.ADL.name);
            }
            if (requirements.isEmpty()) {
                addRequirement(requirements, Requirement.STRIPS.name);
            }
        }
        return requirements;
    }

    private static void addRequirement(Set<String> requirements, String requirement) {
        requirements.add(requirement);
        if (requirement.equalsIgnoreCase(Requirement.QUANTIFIED_PRECONDITIONS.name)) {
            addRequirement(requirements, Requirement.EXISTENTIAL_PRECONDITIONS.name);
            addRequirement(requirements, Requirement.UNIVERSAL_PRECONDITIONS.name);
        }
        if (requirement.equalsIgnoreCase(Requirement.FLUENTS.name)) {
            addRequirement(requirements, Requirement.NUMERIC_FLUENTS.name);
            addRequirement(requirements, Requirement.OBJECT_FLUENTS.name);
        }
        if (requirement.equalsIgnoreCase(Requirement.ADL.name)) {
            addRequirement(requirements, Requirement.STRIPS.name);
            addRequirement(requirements, Requirement.TYPING.name);
            addRequirement(requirements, Requirement.NEGATIVE_PRECONDITIONS.name);
            addRequirement(requirements, Requirement.DISJUNCTIVE_PRECONDITIONS.name);
            addRequirement(requirements, Requirement.EQUALITY.name);
            addRequirement(requirements, Requirement.QUANTIFIED_PRECONDITIONS.name);
            addRequirement(requirements, Requirement.CONDITIONAL_EFFECTS.name);
        }
        if (requirement.equalsIgnoreCase(Requirement.ACTION_COSTS.name)) {
            addRequirement(requirements, Requirement.NUMERIC_FLUENTS.name);
        }
        if (requirement.equalsIgnoreCase(Requirement.GOAL_UTILITIES.name)) {
            addRequirement(requirements, Requirement.PREFERENCES.name);
        }
    }

    enum Requirement {
        STRIPS(":strips"), TYPING(":typing"), NEGATIVE_PRECONDITIONS(":negative-preconditions"),
        DISJUNCTIVE_PRECONDITIONS(":disjunctive-preconditions"), EQUALITY(":equality"),
        EXISTENTIAL_PRECONDITIONS(":existential-preconditions"), UNIVERSAL_PRECONDITIONS(":universal-preconditions"),
        QUANTIFIED_PRECONDITIONS(":quantified-preconditions"), CONDITIONAL_EFFECTS(":conditional-effects"),
        FLUENTS(":fluents"), OBJECT_FLUENTS(":object-fluents"), NUMERIC_FLUENTS(":numeric-fluents"), ADL(":adl"),
        DURATIVE_ACTIONS(":durative-actions"), DURATION_INEQUALITIES(":duration-inequalities"),
        CONTINUOUS_EFFECTS(":continuous-effects"), DERIVED_PREDICATES(":derived-predicates"),
        TIMED_INITIAL_LITERALS(":timed-initial-literals"), PREFERENCES(":preferences"), CONSRTRAINTS(":constraints"),
        ACTION_COSTS(":action-costs"), GOAL_UTILITIES(":goal-utilities");
        public final String name;

        private Requirement(String name) {
            this.name = name;
        }
    }

    private PDDLRequirements() {
    }
}