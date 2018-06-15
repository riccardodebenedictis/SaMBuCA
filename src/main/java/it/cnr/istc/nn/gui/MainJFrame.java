package it.cnr.istc.nn.gui;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JProgressBar;

import it.cnr.istc.nn.Network;
import it.cnr.istc.nn.NetworkListener;

/**
 * MainJFrame
 */
public class MainJFrame extends JFrame implements NetworkListener {

    private static final long serialVersionUID = 1L;
    private final Network nn;
    private final ErrorJPanel error_panel = new ErrorJPanel();
    private final JProgressBar bar = new JProgressBar();

    public MainJFrame(Network nn) {
        super("SaMBuCA");
        this.nn = nn;
        this.nn.addListener(this);

        add(error_panel, BorderLayout.CENTER);

        bar.setStringPainted(true);
        add(bar, BorderLayout.SOUTH);

        setPreferredSize(new Dimension(800, 600));
        pack();
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    /**
     * @return the neural network.
     */
    public Network getNetwork() {
        return nn;
    }

    @Override
    public void start_training(int n_epochs, double tr_error, double evl_error) {
        error_panel.start_training(n_epochs, tr_error, evl_error);
        bar.setValue(0);
        bar.setMaximum(n_epochs);
    }

    @Override
    public void epoch(double tr_error, double evl_error) {
        error_panel.epoch(tr_error, evl_error);
        bar.setValue(bar.getValue() + 1);
    }
}