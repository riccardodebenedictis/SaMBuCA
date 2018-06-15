package it.cnr.istc.nn;

import java.util.Random;

import it.cnr.istc.nn.activation.ActivationFunction;

/**
 * Layer
 */
public class Layer {

    public final int lr_size; // the number of neurons..
    public final int nr_size; // the number of synapsis for each neuron..
    public final ActivationFunction af; // the activation function..
    final double[][] w; // the weights of the layer..
    final double[] b; // the biases of the layer..
    final double[] z; // the weighted inputs to the neurons..
    final double[] a; // the outputs of the neurons..
    final double[] delta; // the delta errors of the neurons..
    final double[][] nabla_w; // the partial derivative of the neurons..
    final double[] nabla_b; // the derivative of the biases..
    final double[][] last_nabla_w; // the last partial derivative of the neurons (for momentum)..
    final double[] last_nabla_b; // the last derivative of the biases (for momentum)..

    public Layer(final int lr_size, final int nr_size, final ActivationFunction af, final Random rnd) {
        this.lr_size = lr_size;
        this.nr_size = nr_size;
        this.af = af;
        w = new double[lr_size][nr_size];
        b = new double[lr_size];
        z = new double[lr_size];
        a = new double[lr_size];
        delta = new double[lr_size];
        nabla_w = new double[lr_size][nr_size];
        nabla_b = new double[lr_size];
        last_nabla_w = new double[lr_size][nr_size];
        last_nabla_b = new double[lr_size];

        // we initialize the weights and the biases..
        for (int i = 0; i < lr_size; ++i) {
            for (int j = 0; j < nr_size; ++j)
                w[i][j] = rnd.nextGaussian() / Math.sqrt(nr_size);
            b[i] = rnd.nextGaussian();
        }
    }

    public double[] forward(final double[] x) {
        assert x.length == nr_size;
        for (int i = 0; i < lr_size; ++i) {
            z[i] = b[i];
            for (int j = 0; j < nr_size; ++j)
                z[i] += w[i][j] * x[j];
            a[i] = af.compute(z[i]);
        }
        return a;
    }
}