package it.cnr.istc.sambuca;

import java.io.IOException;

import it.cnr.istc.neon.Network;
import it.cnr.istc.neon.activation.Sigmoid;
import it.cnr.istc.neon.error.CrossEntropy;
import it.cnr.istc.sambuca.parser.PDDLLanguageParser;
import it.cnr.istc.sambuca.parser.Predicate;
import it.cnr.istc.sambuca.parser.ProblemInstance;
import it.cnr.istc.sambuca.parser.Term;
import it.cnr.istc.sambuca.parser.Variable;

/**
 * SaMBuCA
 */
public class SaMBuCA {

    private final Network nn;
    private final ProblemInstance pi;

    public SaMBuCA(String domain_path, String problem_path) throws IOException {
        this.pi = PDDLLanguageParser.parse(domain_path, problem_path);

        int input_size = 0;
        for (Predicate p : pi.getDomain().getPredicates().values()) {
            int c_size = 1;
            for (Variable v : p.getVariables()) {
                c_size *= v.getType().getInstances().size();
            }
            input_size += c_size;
        }

        for (Term t : pi.getProblem().getInitEls()) {
            System.out.println(t);
        }
        this.nn = new Network(new CrossEntropy(), new Sigmoid(), input_size, 8, 8, 1);
    }
}