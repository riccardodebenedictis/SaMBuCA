package it.cnr.istc.nn.error;

import it.cnr.istc.nn.activation.ActivationFunction;

/**
 * ErrorFunction
 */
public interface ErrorFunction {

    public double error(double[] a, double[] y);

    public double[] delta(ActivationFunction af, double[] z, double[] a, double[] y);
}