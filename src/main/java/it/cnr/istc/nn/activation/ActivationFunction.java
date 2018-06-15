package it.cnr.istc.nn.activation;

/**
 * Activation function.
 */
public interface ActivationFunction {

    public double compute(double v);

    public double derivative(double v);
}