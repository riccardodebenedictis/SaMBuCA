package it.cnr.istc.nn.activation;

/**
 * Linear
 */
public class Linear implements ActivationFunction {

    @Override
    public double compute(double v) {
        return v;
    }

    @Override
    public double derivative(double v) {
        return 1;
    }
}