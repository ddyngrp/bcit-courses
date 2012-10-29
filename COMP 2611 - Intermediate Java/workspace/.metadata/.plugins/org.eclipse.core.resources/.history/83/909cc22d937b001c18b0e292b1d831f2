/*
 * ExtendedDnDDemo.java is a 1.4 example that requires the
 * following files:
 *     StringTransferHandler.java
 *     ListTransferHandler.java
 *     TableTransferHandler.java
 */
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.datatransfer.*;
import java.awt.event.*;

public class ExtendedDnDDemo extends JPanel {
    
    public ExtendedDnDDemo() {
        super(new GridLayout(3,1));
        add(createArea());
        add(createList());
        add(createTable());
    }
    
    private JPanel createList() {
        DefaultListModel listModel = new DefaultListModel();
        listModel.addElement("List 0");
        listModel.addElement("List 1");
        listModel.addElement("List 2");
        listModel.addElement("List 3");
        listModel.addElement("List 4");
        listModel.addElement("List 5");
        listModel.addElement("List 6");
        listModel.addElement("List 7");
        listModel.addElement("List 8");
        
        JList list = new JList(listModel);
        list.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
        JScrollPane scrollPane = new JScrollPane(list);
        scrollPane.setPreferredSize(new Dimension(400,100));
        
        list.setDragEnabled(true);
        list.setTransferHandler(new ListTransferHandler());
        
        JPanel panel = new JPanel(new BorderLayout());
        panel.add(scrollPane, BorderLayout.CENTER);
        panel.setBorder(BorderFactory.createTitledBorder("List"));
        return panel;
    }
    
    private JPanel createArea() {
        String text = "This is the text that I want to show.";
        
        JTextArea area = new JTextArea();
        area.setText(text);
        area.setDragEnabled(true);
        JScrollPane scrollPane = new JScrollPane(area);
        scrollPane.setPreferredSize(new Dimension(400,100));
        JPanel panel = new JPanel(new BorderLayout());
        panel.add(scrollPane, BorderLayout.CENTER);
        panel.setBorder(BorderFactory.createTitledBorder("Text Area"));
        return panel;
    }

    private JPanel createTable() {
        DefaultTableModel model = new DefaultTableModel();
        
        model.addColumn("Column 0");
        model.addColumn("Column 1");
        model.addColumn("Column 2");
        model.addColumn("Column 3");
        
        model.addRow(new String[]{"Table 00", "Table 01",
                                  "Table 02", "Table 03"});
        model.addRow(new String[]{"Table 10", "Table 11",
                                  "Table 12", "Table 13"});
        model.addRow(new String[]{"Table 20", "Table 21",
                                  "Table 22", "Table 23"});
        model.addRow(new String[]{"Table 30", "Table 31",
                                  "Table 32", "Table 33"});

        JTable table = new JTable(model);
        table.getTableHeader().setReorderingAllowed(false);
        table.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);

        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setPreferredSize(new Dimension(400,100));

        table.setDragEnabled(true);
        table.setTransferHandler(new TableTransferHandler());

        JPanel panel = new JPanel(new BorderLayout());
        panel.add(scrollPane, BorderLayout.CENTER);
        panel.setBorder(BorderFactory.createTitledBorder("Table"));
        return panel;
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
        JFrame frame = new JFrame("ExtendedDnDDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new ExtendedDnDDemo();
        newContentPane.setOpaque(true); //content panes must be opaque
        frame.setContentPane(newContentPane);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
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
