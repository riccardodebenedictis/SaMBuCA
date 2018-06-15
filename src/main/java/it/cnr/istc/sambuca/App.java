package it.cnr.istc.sambuca;

import it.cnr.istc.nn.DataRow;
import it.cnr.istc.nn.Network;
import it.cnr.istc.nn.activation.Sigmoid;
import it.cnr.istc.nn.error.CrossEntropy;
import it.cnr.istc.nn.gui.MainJFrame;

/**
 * Hello world!
 *
 */
public class App {

    public static void main(String[] args) {
        Network nn = new Network(new CrossEntropy(), new Sigmoid(), 2, 8, 8, 1);

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

        MainJFrame frame = new MainJFrame(nn);
        frame.setVisible(true);

        // we train the network through stochastic gradient descent..
        nn.sgd(tr_data, evl_data, 20000, 2, 0.05, 0, 0);

        // this is the current error on training data after the training..
        double t_err = nn.getError(tr_data);
    }
}
