package it.cnr.istc.nn;

/**
 * NetworkListener
 */
public interface NetworkListener {

    public void start_training(int n_epochs, double tr_error, double evl_error);

    public void epoch(double tr_error, double evl_error);
}