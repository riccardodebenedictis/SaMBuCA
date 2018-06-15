package it.cnr.istc.nn.error;

import it.cnr.istc.nn.activation.ActivationFunction;

/**
 * ErrorFunction
 */
public interface ErrorFunction {

    public double error(final double[] a, final double[] y);

    public double[] delta(final ActivationFunction af, final double[] z, final double[] a, final double[] y);
}