package it.cnr.istc.nn;

import java.util.Arrays;
import java.util.Random;

import it.cnr.istc.nn.activation.ActivationFunction;
import it.cnr.istc.nn.error.ErrorFunction;

/**
 * This class is intended to represent Artificial Neural Network instances.
 */
public class Network {

    private final Random rnd; // the random number generator..
    private final ErrorFunction ef; // the error function..
    private final Layer[] layers; // the layers..

    public Network(final ErrorFunction ef, final ActivationFunction af, final int... sizes) {
        this.rnd = new Random();
        this.ef = ef;
        this.layers = new Layer[sizes.length];

        // we initialize the layers..
        for (int i = 0; i < sizes.length - 1; ++i)
            layers[i] = new Layer(sizes[i + 1], sizes[i], af, rnd);
    }

    /**
     * Performs forward propagation.
     * 
     * @param x an array of double representing the input to the network.
     * @return an array of double representing the output of the network to the
     *         input {@code x}.
     */
    public double[] forward(final double[] x) {
        double[] a = layers[0].forward(x);
        for (int i = 1; i < layers.length; ++i)
            a = layers[i].forward(a);
        return a;
    }

    /**
     * Computes the error of the network to the given data.
     * 
     * @param data an array of data rows.
     * @return a double representing the error of the network to the given data.
     */
    public double getError(final DataRow... data) {
        double err = 0;
        for (DataRow d : data)
            err += ef.error(forward(d.x), d.y);
        return err / data.length;
    }

    /**
     * Performs Stochastic Gradient Descent (SGD) on the given training data.
     * 
     * @param tr_data         an array of 'DataRow's representing the training data.
     * @param eval_data       an array of 'DataRow's representing the evaluation
     *                        data (might be useful for meta-parameters
     *                        initialization).
     * @param epochs          a positive integer representing the number of epochs
     *                        (i.e. the number of performed training steps).
     * @param mini_batch_size a positive integer representing the size of the
     *                        mini-batch.
     * @param eta             a positive real representing the learning rate.
     * @param mu              a positive (and strictly less than one) real
     *                        representing the momentum.
     * @param lambda          a positive real representing the regularization
     *                        parameter.
     */
    public void sgd(final DataRow[] tr_data, final DataRow[] eval_data, final int epochs, final int mini_batch_size,
            final double eta, final double mu, double lambda) {
        for (int i = 1; i <= epochs; ++i) {
            // we shuffle the training data..
            shuffle(rnd, tr_data);
            // we partition the training data into mini batches of 'mini_batch_size' size..
            for (int j = 0; j <= tr_data.length - mini_batch_size; j += mini_batch_size)
                update_mini_batch(Arrays.copyOfRange(tr_data, j, j + mini_batch_size), eta, mu, lambda);
        }
    }

    private void update_mini_batch(final DataRow[] mini_batch, final double eta, final double mu, final double lambda) {
        // we perform backpropagation..
        for (DataRow data : mini_batch)
            backprop(data);

        // we update the biases, the weigths, and clean up things..
        for (int i = 0; i < layers.length; ++i)
            for (int j = 0; j < layers[i].lr_size; ++j) {
                layers[i].b[j] -= (eta / mini_batch.length) * layers[i].nabla_b[j] + mu * layers[i].last_nabla_b[j];
                layers[i].last_nabla_b[j] = layers[i].nabla_b[j];
                layers[i].nabla_b[j] = 0;
                for (int k = 0; k < layers[i].nr_size; ++k) {
                    layers[i].w[j][k] -= (eta / mini_batch.length) * layers[i].nabla_w[j][k]
                            + ((eta * lambda) / mini_batch.length) * layers[i].w[j][k]
                            + mu * layers[i].last_nabla_w[j][k];
                    layers[i].last_nabla_w[j][k] = layers[i].nabla_w[j][k];
                }
                Arrays.fill(layers[i].nabla_w[j], 0);
            }
    }

    private void backprop(DataRow data) {
        // feedforward..
        double[] a = forward(data.x);

        // we compute the deltas for the output layer..
        System.arraycopy(ef.delta(layers[layers.length - 1].af, layers[layers.length - 1].z, a, data.y), 0,
                layers[layers.length - 1].delta, 0, layers[layers.length - 1].delta.length);

        // we compute the deltas for the other layers..
        for (int i = layers.length - 1; i > 0; --i)
            for (int j = 0; j < layers[i - 1].lr_size; ++j) {
                layers[i - 1].delta[j] = 0;
                for (int k = 0; k < layers[i].lr_size; ++k)
                    layers[i - 1].delta[j] += layers[i].w[k][j] * layers[i].delta[k];
                layers[i - 1].delta[j] *= layers[i - 1].z[j];
            }

        // we use the computed deltas to update the nablas..
        for (int i = layers.length - 1; i >= 1; --i)
            for (int j = 0; j < layers[i].lr_size; ++j) {
                layers[i].nabla_b[j] += layers[i].delta[j];
                for (int k = 0; k < layers[i - 1].lr_size; ++k)
                    layers[i].nabla_w[j][k] += layers[i - 1].a[k] * layers[i].delta[j];
            }

        for (int i = 0; i < layers[0].lr_size; ++i) {
            layers[0].nabla_b[i] += layers[0].delta[i];
            for (int k = 0; k < data.x.length; ++k)
                layers[0].nabla_w[i][k] += data.x[k] * layers[0].delta[i];
        }
    }

    // Fisher–Yates shuffle..
    static <T> void shuffle(final Random rnd, final T[] ar) {
        for (int i = ar.length - 1; i > 0; i--) {
            int index = rnd.nextInt(i + 1);
            // simple swap..
            T a = ar[index];
            ar[index] = ar[i];
            ar[i] = a;
        }
    }
}