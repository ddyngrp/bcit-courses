import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.NumberFormatter;
import java.beans.*;

/*
 * SliderDemo3.java is a 1.4 application that requires all the
 * files in the images/doggy directory.  It adds a formatted text
 * field to SliderDemo.java.
 */
public class SliderDemo3 extends JPanel
                         implements ActionListener,
                                    WindowListener,
                                    ChangeListener,
                                    PropertyChangeListener {
    //Set up animation parameters.
    static final int FPS_MIN = 0;
    static final int FPS_MAX = 30;
    static final int FPS_INIT = 15;    //initial frames per second
    int frameNumber = 0;
    int NUM_FRAMES = 14;
    ImageIcon[] images = new ImageIcon[NUM_FRAMES];
    int delay;
    Timer timer;
    boolean frozen = false;

    //This label uses ImageIcon to show the doggy pictures.
    JLabel picture;

    //Add a formatted text field to supplement the slider.
    JFormattedTextField textField;

    //And here's the slider.
    JSlider framesPerSecond;

    public SliderDemo3() {
        setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));

        delay = 1000 / FPS_INIT;

        //Create the label.
        JLabel sliderLabel = new JLabel("Frames Per Second: ", JLabel.CENTER);
        sliderLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        //Create the formatted text field and its formatter.
        java.text.NumberFormat numberFormat =
            java.text.NumberFormat.getIntegerInstance();
        NumberFormatter formatter = new NumberFormatter(numberFormat);
        formatter.setMinimum(new Integer(FPS_MIN));
        formatter.setMaximum(new Integer(FPS_MAX));
        textField = new JFormattedTextField(formatter);
        textField.setValue(new Integer(FPS_INIT));
        textField.setColumns(5); //get some space
        textField.addPropertyChangeListener(this);

        //React when the user presses Enter.
        textField.getInputMap().put(KeyStroke.getKeyStroke(
                                        KeyEvent.VK_ENTER, 0),
                                        "check");
        textField.getActionMap().put("check", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                if (!textField.isEditValid()) { //The text is invalid.
                    Toolkit.getDefaultToolkit().beep();
                    textField.selectAll();
                } else try {                    //The text is valid,
                    textField.commitEdit();     //so use it.
                } catch (java.text.ParseException exc) { }
            }
        });
        //XXX:  Neither actionPerformed nor invalidEdit gets invoked
        //      when the user tries to make an invalid edit -- e.g.,
        //      typing 100 and pressing Enter.  There's no beep, seemingly
        //      no opportunity to respond to the incorrect value.
        //      I fixed this by adding an action for Enter, which made
        //      the text field's action listener never get called, so I
        //      removed the action listener.

        //Create the slider.
        framesPerSecond = new JSlider(JSlider.HORIZONTAL,
                                      FPS_MIN, FPS_MAX, FPS_INIT);
        framesPerSecond.addChangeListener(this);

        //Turn on labels at major tick marks.
        framesPerSecond.setMajorTickSpacing(10);
        framesPerSecond.setMinorTickSpacing(1);
        framesPerSecond.setPaintTicks(true);
        framesPerSecond.setPaintLabels(true);
        framesPerSecond.setBorder(
                BorderFactory.createEmptyBorder(0,0,10,0));

        //Create the label that displays the animation.
        picture = new JLabel();
        picture.setHorizontalAlignment(JLabel.CENTER);
        picture.setAlignmentX(Component.CENTER_ALIGNMENT);
        picture.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLoweredBevelBorder(),
                BorderFactory.createEmptyBorder(10,10,10,10)));
        updatePicture(0); //display first frame

        //Create a subpanel for the label and text field.
        JPanel labelAndTextField = new JPanel(); //use FlowLayout
        labelAndTextField.add(sliderLabel);
        labelAndTextField.add(textField);

        //Put everything together.
        add(labelAndTextField);
        add(framesPerSecond);
        add(picture);
        setBorder(BorderFactory.createEmptyBorder(10,10,10,10));

        //Set up a timer that calls this object's action handler.
        timer = new Timer(delay, this);
        timer.setInitialDelay(delay * 7); //We pause animation twice per cycle
                                          //by restarting the timer
        timer.setCoalesce(true);
    }

    /** Add a listener for window events. */
    void addWindowListener(Window w) {
        w.addWindowListener(this);
    }

    //React to window events.
    public void windowIconified(WindowEvent e) {
        stopAnimation();
    }
    public void windowDeiconified(WindowEvent e) {
        startAnimation();
    }
    public void windowOpened(WindowEvent e) {}
    public void windowClosing(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}

    /** Listen to the slider. */
    public void stateChanged(ChangeEvent e) {
        JSlider source = (JSlider)e.getSource();
        int fps = (int)source.getValue();
        if (!source.getValueIsAdjusting()) { //done adjusting
            textField.setValue(new Integer(fps)); //update ftf value
            if (fps == 0) {
                if (!frozen) stopAnimation();
            } else {
                delay = 1000 / fps;
                timer.setDelay(delay);
                timer.setInitialDelay(delay * 10);
                if (frozen) startAnimation();
            }
        } else { //value is adjusting; just set the text
            textField.setText(String.valueOf(fps));
        }
    }

    /**
     * Listen to the text field.  This method detects when the
     * value of the text field (not necessarily the same
     * number as you'd get from getText) changes.
     */
    public void propertyChange(PropertyChangeEvent e) {
        if ("value".equals(e.getPropertyName())) {
            Number value = (Number)e.getNewValue();
            if (framesPerSecond != null && value != null) {
                framesPerSecond.setValue(value.intValue());
            }
        }
    }

    public void startAnimation() {
        //Start (or restart) animating!
        timer.start();
        frozen = false;
    }

    public void stopAnimation() {
        //Stop the animating thread.
        timer.stop();
        frozen = true;
    }

    //Called when the Timer fires.
    public void actionPerformed(ActionEvent e) {
        //Advance the animation frame.
        if (frameNumber == (NUM_FRAMES - 1)) {
            frameNumber = 0;
        } else {
            frameNumber++;
        }

        updatePicture(frameNumber); //display the next picture

        if ( frameNumber==(NUM_FRAMES - 1)
          || frameNumber==(NUM_FRAMES/2 - 1) ) {
            timer.restart();
        }
    }

    /** Update the label to display the image for the current frame. */
    protected void updatePicture(int frameNum) {
        //Get the image if we haven't already.
        if (images[frameNumber] == null) {
            images[frameNumber] = createImageIcon("images/doggy/T"
                                                  + frameNumber
                                                  + ".gif");
        }

        //Set the image.
        if (images[frameNumber] != null) {
            picture.setIcon(images[frameNumber]);
        } else { //image not found
            picture.setText("image #" + frameNumber + " not found");
        }
    }

    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = SliderDemo3.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }

    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("SliderDemo3");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        SliderDemo3 animator = new SliderDemo3();
        animator.setOpaque(true); //content panes must be opaque
        frame.setContentPane(animator);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
        animator.startAnimation(); 
    }

    public static void main(String[] args) {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }
}
