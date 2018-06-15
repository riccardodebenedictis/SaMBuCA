package it.cnr.istc.nn.gui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;

import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

import it.cnr.istc.nn.NetworkListener;

/**
 * ErrorJPanel
 */
public class ErrorJPanel extends JPanel implements NetworkListener {

    private static final long serialVersionUID = 1L;
    private final TimeSeries tr_data_error = new TimeSeries("Training data");
    private final TimeSeries tst_data_error = new TimeSeries("Evaluation data");
    private final TimeSeriesCollection collection = new TimeSeriesCollection();
    private final JFreeChart chart = ChartFactory.createTimeSeriesChart("Error", "", "Error", collection);
    private final ChartPanel chart_panel = new ChartPanel(chart);

    public ErrorJPanel() {
        super(new BorderLayout());
        collection.addSeries(tr_data_error);
        collection.addSeries(tst_data_error);

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        chart_panel.setMaximumDrawWidth(screenSize.width);
        chart_panel.setMaximumDrawHeight(screenSize.height);
        add(chart_panel);
    }

    @Override
    public void start_training(int n_epochs, double tr_error, double evl_error) {
        tr_data_error.addOrUpdate(new Millisecond(), tr_error);
        tst_data_error.addOrUpdate(new Millisecond(), evl_error);
    }

    @Override
    public void epoch(double tr_error, double evl_error) {
        tr_data_error.addOrUpdate(new Millisecond(), tr_error);
        tst_data_error.addOrUpdate(new Millisecond(), evl_error);
    }
}