package it.cnr.istc.neon.activation;

/**
 * Linear
 */
public class Linear implements ActivationFunction {

    @Override
    public double compute(final double v) {
        return v;
    }

    @Override
    public double derivative(final double v) {
        return 1;
    }
}