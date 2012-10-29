/*
 * TabbedPaneController.java is used by the 1.4 
 * DragFileDemo.java example.
 */
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

/*
 * Class that manages area where the contents of
 * files are displayed.  When no files are present,
 * there is a simple JTextArea instructing users
 * to drop a file.  As soon as a file is dropped,
 * a JTabbedPane is placed into the window and
 * each file is displayed under its own tab.
 * When all the files are removed, the JTabbedPane
 * is removed from the window and the simple
 * JTextArea is again displayed.
 */
public class TabbedPaneController {
    JPanel tabbedPanel = null;
    JTabbedPane tabbedPane;
    JPanel emptyFilePanel = null;
    JTextArea emptyFileArea = null;
    FileAndTextTransferHandler transferHandler;
    boolean noFiles = true;
    String fileSeparator;

    public TabbedPaneController(JTabbedPane tb, JPanel tp) {
        tabbedPane = tb;
        tabbedPanel = tp;
        transferHandler = new FileAndTextTransferHandler(this);
        fileSeparator = System.getProperty("file.separator");
        //The split method in the String class uses
        //regular expressions to define the text used for
        //the split.  The forward slash "\" is a special
        //character and must be escaped.  Some look and feels,
        //such as Microsoft Windows, use the forward slash to
        //delimit the path.
        if ("\\".equals(fileSeparator)) {
            fileSeparator = "\\\\";
        }
        init();
    }

    public JTextArea addTab(String filename) {
        if (noFiles) {
            tabbedPanel.remove(emptyFilePanel);
            tabbedPanel.add(tabbedPane, BorderLayout.CENTER);
            noFiles = false;
        }
        String[] str = filename.split(fileSeparator);
        return makeTextPanel(str[str.length-1], filename);
    }

    //Remove all tabs and their components, then put the default
    //file area back.
    public void clearAll() {
        if (noFiles == false) {
            tabbedPane.removeAll();
            tabbedPanel.remove(tabbedPane);
        }
        init();
    }

    private void init() {
        String defaultText = 
            "Select one or more files from the file chooser and drop here...";
        noFiles = true;
        if (emptyFilePanel == null) {
            emptyFileArea = new JTextArea(20,15);
            emptyFileArea.setEditable(false);
            emptyFileArea.setDragEnabled(true);
            emptyFileArea.setTransferHandler(transferHandler);
            emptyFileArea.setMargin(new Insets(5,5,5,5));
            JScrollPane fileScrollPane = new JScrollPane(emptyFileArea);
            emptyFilePanel = new JPanel(new BorderLayout(), false);
            emptyFilePanel.add(fileScrollPane, BorderLayout.CENTER);
        }
        tabbedPanel.add(emptyFilePanel, BorderLayout.CENTER);
        tabbedPanel.repaint();
        emptyFileArea.setText(defaultText);
    }

    protected JTextArea makeTextPanel(String name, String toolTip) {
        JTextArea fileArea = new JTextArea(20,15);
        fileArea.setDragEnabled(true);
        fileArea.setTransferHandler(transferHandler);
        fileArea.setMargin(new Insets(5,5,5,5));
        JScrollPane fileScrollPane = new JScrollPane(fileArea);
        tabbedPane.addTab(name, null, (Component)fileScrollPane, toolTip);
        tabbedPane.setSelectedComponent((Component)fileScrollPane);
        return fileArea;
    }
}
