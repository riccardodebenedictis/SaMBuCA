package it.cnr.istc.neon.activation;

/**
 * Activation function.
 */
public interface ActivationFunction {

    public double compute(final double v);

    public double derivative(final double v);
}