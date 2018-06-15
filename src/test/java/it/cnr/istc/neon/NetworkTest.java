package it.cnr.istc.neon;

import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import it.cnr.istc.neon.activation.Sigmoid;
import it.cnr.istc.neon.error.CrossEntropy;
import it.cnr.istc.neon.error.MeanSquaredError;

/**
 * Tests the artificial neural network
 */
public class NetworkTest {

    @Test
    public void test0() {
        Network nn = new Network(new MeanSquaredError(), new Sigmoid(), 2, 3, 1);

        // we create some the training data..
        DataRow[] tr_data = new DataRow[] { new DataRow(new double[] { 3, 5 }, new double[] { 0.75 }),
                new DataRow(new double[] { 5, 1 }, new double[] { 0.82 }),
                new DataRow(new double[] { 10, 2 }, new double[] { 0.93 }) };

        // we create the some evaluation data..
        DataRow[] evl_data = new DataRow[] { new DataRow(new double[] { 3, 5 }, new double[] { 0.75 }),
                new DataRow(new double[] { 5, 1 }, new double[] { 0.82 }),
                new DataRow(new double[] { 10, 2 }, new double[] { 0.93 }) };

        // this is the current error on training data before the training..
        double c_err = nn.getError(tr_data);

        // we train the network through stochastic gradient descent..
        nn.sgd(tr_data, evl_data, 200, 3, 3, 0, 0.1);

        // this is the current error on training data after the training..
        double t_err = nn.getError(tr_data);
        assertTrue(c_err > t_err);
    }

    @Test
    public void test1() {
        Network nn = new Network(new CrossEntropy(), new Sigmoid(), 2, 4, 4, 1);

        // we create some the training data..
        DataRow[] tr_data = new DataRow[] { new DataRow(new double[] { 0, 0 }, new double[] { 0 }),
                new DataRow(new double[] { 0, 1 }, new double[] { 1 }),
                new DataRow(new double[] { 1, 0 }, new double[] { 1 }),
                new DataRow(new double[] { 1, 1 }, new double[] { 0 }) };

        // we create the some evaluation data..
        DataRow[] evl_data = new DataRow[] { new DataRow(new double[] { 0, 0 }, new double[] { 0 }),
                new DataRow(new double[] { 0, 1 }, new double[] { 1 }),
                new DataRow(new double[] { 1, 0 }, new double[] { 1 }),
                new DataRow(new double[] { 1, 1 }, new double[] { 0 }) };

        // this is the current error on training data before the training..
        double c_err = nn.getError(tr_data);

        // we train the network through stochastic gradient descent..
        nn.sgd(tr_data, evl_data, 20000, 2, 0.05, 0, 0);

        // this is the current error on training data after the training..
        double t_err = nn.getError(tr_data);
        assertTrue(c_err > t_err);
    }
}
