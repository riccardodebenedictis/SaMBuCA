package it.cnr.istc.neon.error;

import it.cnr.istc.neon.activation.ActivationFunction;

/**
 * CrossEntropy
 */
public class CrossEntropy implements ErrorFunction {

    @Override
    public double error(final double[] a, final double[] y) {
        assert a.length == y.length;
        double err = 0;
        for (int i = 0; i < a.length; ++i)
            err += y[i] * Math.log(a[i]) + (1 - y[i]) * Math.log(1 - a[i]);
        return Double.isNaN(err) ? 0 : -err;
    }

    @Override
    public double[] delta(final ActivationFunction af, final double[] z, final double[] a, final double[] y) {
        assert z.length == a.length;
        assert a.length == y.length;
        double[] d = new double[a.length];
        for (int i = 0; i < a.length; ++i)
            d[i] = a[i] - y[i];
        return d;
    }
}