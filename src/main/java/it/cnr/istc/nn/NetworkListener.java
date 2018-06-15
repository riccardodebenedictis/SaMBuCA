package it.cnr.istc.nn;

/**
 * NetworkListener
 */
public interface NetworkListener {

    public void start_training(int n_epochs, double tr_error, double evl_error);

    public void stop_training(double tr_error, double evl_error);

    public void start_epoch(double tr_error, double evl_error);

    public void stop_epoch(double tr_error, double evl_error);
}