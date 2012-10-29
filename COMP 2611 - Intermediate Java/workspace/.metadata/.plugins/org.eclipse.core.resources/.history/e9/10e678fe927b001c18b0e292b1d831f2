/*
 * A 1.4 example that uses the following files:
 *    GenealogyModel.java
 *    Person.java
 *
 * Based on an example provided by tutorial reader Olivier Berlanger.
 */
import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GenealogyExample extends JPanel 
                              implements ActionListener {
    GenealogyTree tree;
    private static String SHOW_ANCESTOR_CMD = "showAncestor";

    public GenealogyExample() {
        super(new BorderLayout());
        
        //Construct the panel with the toggle buttons.
        JRadioButton showDescendant = 
                new JRadioButton("Show descendants", true);
        final JRadioButton showAncestor = 
                new JRadioButton("Show ancestors");
        ButtonGroup bGroup = new ButtonGroup();
        bGroup.add(showDescendant);
        bGroup.add(showAncestor);
        showDescendant.addActionListener(this);
        showAncestor.addActionListener(this);
        showAncestor.setActionCommand(SHOW_ANCESTOR_CMD);
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(showDescendant);
        buttonPanel.add(showAncestor);

        //Construct the tree.
        tree = new GenealogyTree(getGenealogyGraph());
        JScrollPane scrollPane = new JScrollPane(tree);
        scrollPane.setPreferredSize(new Dimension(200, 200));

        //Add everything to this panel.
        add(buttonPanel, BorderLayout.PAGE_START);
        add(scrollPane, BorderLayout.CENTER);
    }

    /** 
     * Required by the ActionListener interface.
     * Handle events on the showDescendant and
     * showAncestore buttons. 
     */
    public void actionPerformed(ActionEvent ae) {
        if (ae.getActionCommand() == SHOW_ANCESTOR_CMD) {
            tree.showAncestor(true);
        } else {
            tree.showAncestor(false);
        }
    }
    
    /**
     *  Constructs the genealogy graph used by the model.
     */
    public Person getGenealogyGraph() {
        //the greatgrandparent generation
        Person a1 = new Person("Jack (great-granddaddy)");
        Person a2 = new Person("Jean (great-granny)");
        Person a3 = new Person("Albert (great-granddaddy)");
        Person a4 = new Person("Rae (great-granny)");
        Person a5 = new Person("Paul (great-granddaddy)");
        Person a6 = new Person("Josie (great-granny)");

        //the grandparent generation
        Person b1 = new Person("Peter (grandpa)");
        Person b2 = new Person("Zoe (grandma)");
        Person b3 = new Person("Simon (grandpa)");
        Person b4 = new Person("James (grandpa)");
        Person b5 = new Person("Bertha (grandma)");
        Person b6 = new Person("Veronica (grandma)");
        Person b7 = new Person("Anne (grandma)");
        Person b8 = new Person("Renee (grandma)");
        Person b9 = new Person("Joseph (grandpa)");

        //the parent generation
        Person c1 = new Person("Isabelle (mom)");
        Person c2 = new Person("Frank (dad)");
        Person c3 = new Person("Louis (dad)");
        Person c4 = new Person("Laurence (dad)");
        Person c5 = new Person("Valerie (mom)");
        Person c6 = new Person("Marie (mom)");
        Person c7 = new Person("Helen (mom)");
        Person c8 = new Person("Mark (dad)");
        Person c9 = new Person("Oliver (dad)");

        //the youngest generation
        Person d1 = new Person("Clement (boy)");
        Person d2 = new Person("Colin (boy)");

        Person.linkFamily(a1,a2,new Person[] {b1,b2,b3,b4});
        Person.linkFamily(a3,a4,new Person[] {b5,b6,b7});
        Person.linkFamily(a5,a6,new Person[] {b8,b9});
        Person.linkFamily(b3,b6,new Person[] {c1,c2,c3});
        Person.linkFamily(b4,b5,new Person[] {c4,c5,c6});
        Person.linkFamily(b8,b7,new Person[] {c7,c8,c9});
        Person.linkFamily(c4,c7,new Person[] {d1,d2});

        return a1;
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
        JFrame frame = new JFrame("GenealogyExample");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        GenealogyExample newContentPane = new GenealogyExample();
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
