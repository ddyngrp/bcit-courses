import javax.swing.Icon;
import javax.swing.JTree;
import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

public class GenealogyTree extends JTree {
    GenealogyModel model;

    public GenealogyTree(Person graphNode) {
        super(new GenealogyModel(graphNode));
        getSelectionModel().setSelectionMode(
                TreeSelectionModel.SINGLE_TREE_SELECTION);
        DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer();
        Icon personIcon = null;
        renderer.setLeafIcon(personIcon);
        renderer.setClosedIcon(personIcon);
        renderer.setOpenIcon(personIcon);
        setCellRenderer(renderer);
    }
    
    /**
     * Get the selected item in the tree, and call showAncestor with this
     * item on the model.
     */
    public void showAncestor(boolean b) {
        Object newRoot = null;
        TreePath path = getSelectionModel().getSelectionPath();
        if (path != null) {
            newRoot = path.getLastPathComponent();
        }
        ((GenealogyModel)getModel()).showAncestor(b, newRoot);
    }
}
