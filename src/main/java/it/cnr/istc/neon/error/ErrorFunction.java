package it.cnr.istc.neon.error;

import it.cnr.istc.neon.activation.ActivationFunction;

/**
 * ErrorFunction
 */
public interface ErrorFunction {

    public double error(final double[] a, final double[] y);

    public double[] delta(final ActivationFunction af, final double[] z, final double[] a, final double[] y);
}