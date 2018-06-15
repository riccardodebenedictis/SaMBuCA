package it.cnr.istc.neon.error;

import it.cnr.istc.neon.activation.ActivationFunction;

/**
 * MeanSquaredError
 */
public class MeanSquaredError implements ErrorFunction {

    @Override
    public double error(final double[] a, final double[] y) {
        assert a.length == y.length;
        double err = 0;
        for (int i = 0; i < a.length; ++i)
            err += Math.pow(a[i] - y[i], 2);
        return err;
    }

    @Override
    public double[] delta(final ActivationFunction af, final double[] z, final double[] a, final double[] y) {
        assert z.length == a.length;
        assert a.length == y.length;
        double[] d = new double[a.length];
        for (int i = 0; i < a.length; ++i)
            d[i] = (a[i] - y[i]) * af.derivative(z[i]);
        return d;
    }
}