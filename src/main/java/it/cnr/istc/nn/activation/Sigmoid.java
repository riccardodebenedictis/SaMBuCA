package it.cnr.istc.nn.activation;

/**
 * Sigmoid activation function.
 */
public class Sigmoid implements ActivationFunction {

    @Override
    public double compute(final double v) {
        if (v > 100)
            return 1.0;
        else if (v < -100)
            return 0.0;
        else
            return (1.0 / (1.0 + Math.exp(-v)));
    }

    @Override
    public double derivative(final double v) {
        return compute(v) * (1.0 - compute(v));
    }
}