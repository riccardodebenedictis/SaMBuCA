package it.cnr.istc.nn;

/**
 * DataRow
 */
public class DataRow {

    public final double[] x;
    public final double[] y;

    public DataRow(final double[] x, final double[] y) {
        this.x = x;
        this.y = y;
    }
}