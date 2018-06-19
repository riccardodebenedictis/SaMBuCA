package it.cnr.istc.sambuca;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import it.cnr.istc.neon.Network;
import it.cnr.istc.neon.activation.Sigmoid;
import it.cnr.istc.neon.error.CrossEntropy;
import it.cnr.istc.sambuca.parser.Constant;
import it.cnr.istc.sambuca.parser.PDDLLanguageParser;
import it.cnr.istc.sambuca.parser.Predicate;
import it.cnr.istc.sambuca.parser.ProblemInstance;
import it.cnr.istc.sambuca.parser.Term;
import it.cnr.istc.sambuca.parser.Variable;

/**
 * SaMBuCA
 */
public class SaMBuCA {

    private final ProblemInstance pi;
    private final Network nn;

    public SaMBuCA(String domain_path, String problem_path) throws IOException {
        this.pi = PDDLLanguageParser.parse(domain_path, problem_path);

        // this is the list of all the ground predicates..
        List<String> ground_preds = new ArrayList<>();
        for (Predicate p : pi.getDomain().getPredicates().values()) {
            List<Variable> vars = p.getVariables();
            if (vars.isEmpty())
                ground_preds.add("(" + p.getName() + ")");
            else {
                Constant[][] cnsts = new Constant[vars.size()][];
                for (int i = 0; i < vars.size(); i++) {
                    cnsts[i] = vars.get(i).getType().getInstances()
                            .toArray(new Constant[vars.get(i).getType().getInstances().size()]);
                }
                for (Constant[] cs : new CartesianProductGenerator<>(cnsts)) {
                    ground_preds.add("(" + p.getName() + " "
                            + Stream.of(cs).map(argument -> argument.toString()).collect(Collectors.joining(" "))
                            + ")");
                }
            }
        }

        // this is the initial state..
        Set<String> init = new HashSet<>();
        for (Term t : pi.getProblem().getInitEls()) {
            init.add(t.toString());
        }

        // we create the neural network..
        this.nn = new Network(new CrossEntropy(), new Sigmoid(), ground_preds.size() * 2, ground_preds.size(),
                ground_preds.size(), 1);
    }
}