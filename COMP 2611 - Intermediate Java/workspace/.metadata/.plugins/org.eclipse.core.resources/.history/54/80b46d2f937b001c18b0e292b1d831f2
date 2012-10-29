/*
 * Works in 1.1+Swing, 1.4, and all releases in between.
 * Used by the Converter example.
 */

import javax.swing.*;
import javax.swing.event.*;

/**
 * Implements a model whose data is actually in another model (the
 * "source model").  The follower model adjusts the values obtained
 * from the source model (or set in the follower model) to be in
 * a different unit of measure.
 *
 */
public class FollowerRangeModel extends ConverterRangeModel
                                implements ChangeListener {
    ConverterRangeModel sourceModel; //the real model

    /** Creates a FollowerRangeModel that gets its state from sourceModel. */
    public FollowerRangeModel(ConverterRangeModel sourceModel) {
        this.sourceModel = sourceModel;
        sourceModel.addChangeListener(this);
    }

    //The only method in the ChangeListener interface.
    public void stateChanged(ChangeEvent e) {
        fireStateChanged();
    }

    public int getMaximum() {
        int modelMax = sourceModel.getMaximum();
        double multiplyBy = sourceModel.getMultiplier()/this.getMultiplier();
        return (int)(modelMax * multiplyBy);
    }

    public void setMaximum(int newMaximum) {
        sourceModel.setMaximum((int)(newMaximum *
                     (this.getMultiplier()/sourceModel.getMultiplier())));
    }

    public int getValue() {
        return (int)getDoubleValue();
    }

    public void setValue(int newValue) {
        setDoubleValue((double)newValue);
    }

    public double getDoubleValue() {
        return sourceModel.getDoubleValue()
               * sourceModel.getMultiplier()
               / this.getMultiplier();
    }

    public void setDoubleValue(double newValue) {
        sourceModel.setDoubleValue(
                     newValue * this.getMultiplier()
                     / sourceModel.getMultiplier());
    }

    public int getExtent() {
        return super.getExtent();
    }

    public void setExtent(int newExtent) {
        super.setExtent(newExtent);
    }

    public void setRangeProperties(int value,
                                   int extent,
                                   int min,
                                   int max,
                                   boolean adjusting) {
        double multiplyBy = this.getMultiplier()/sourceModel.getMultiplier();
        sourceModel.setRangeProperties(value*multiplyBy,
                                     extent, min,
                                     (int)(max*multiplyBy),
                                     adjusting);
    }
}
