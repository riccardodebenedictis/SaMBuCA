package it.cnr.istc.sambuca;

import it.cnr.istc.nn.Network;
import it.cnr.istc.nn.activation.Sigmoid;
import it.cnr.istc.nn.error.MeanSquaredError;
import it.cnr.istc.nn.gui.MainJFrame;

/**
 * Hello world!
 *
 */
public class App {

    public static void main(String[] args) {
        Network nn = new Network(new MeanSquaredError(), new Sigmoid(), 2, 4, 1);

        MainJFrame frame = new MainJFrame(nn);
        frame.setVisible(true);
    }
}
