// Using TreeView to display directory structure.
using System;
using System.Windows.Forms;
using System.IO;

// Form uses TreeView to display directory structure
public partial class TreeViewDirectoryStructureForm : Form
{
   string substringDirectory; // store last part of full path name

   // default constructor
   public TreeViewDirectoryStructureForm()
   {
      InitializeComponent();
   } // end constructor

   // populate current node with subdirectories
   public void PopulateTreeView( 
      string directoryValue, TreeNode parentNode )
   {
      // array stores all subdirectories in the directory
      string[] directoryArray = 
         Directory.GetDirectories( directoryValue );

      // populate current node with subdirectories
      try
      {
         // check to see if any subdirectories are present
         if ( directoryArray.Length != 0 )
         {
            // for every subdirectory, create new TreeNode,
            // add as a child of current node and recursively
            // populate child nodes with subdirectories
            foreach ( string directory in directoryArray )
            {
               // obtain last part of path name from the full path name
               // by finding the last occurence of "\" and returning the
               // part of the path name that comes after this occurrence
               substringDirectory = directory.Substring(
                  directory.LastIndexOf( '\\' ) + 1,
                  directory.Length - directory.LastIndexOf( '\\' ) - 1 );

              
               // To add a root node:
               // myTreeView.Nodes.Add( new TreeNode (rootLabel) ); 
               // To add a child to the root node at index myIndex:
               // myTreeView.Nodes[myIndex].Nodes.Add( new TreeNode (ChildLabel) );


               // create TreeNode for current directory
               TreeNode myNode = new TreeNode( substringDirectory );

               // add current directory node to parent node
               parentNode.Nodes.Add( myNode );

               // recursively populate every subdirectory
               PopulateTreeView( directory, myNode );
            } // end foreach
         } // end if
      } // end try

      // catch exception
      catch ( UnauthorizedAccessException )
      {
         parentNode.Nodes.Add( "Access denied" );
      } // end catch
   } // end method PopulateTreeView

   // handles enterButton click event
   private void enterButton_Click( object sender, EventArgs e )
   {
      // clear all nodes
      directoryTreeView.Nodes.Clear();

      // check if the directory entered by user exists
      // if it does then fill in the TreeView,
      // if not display error MessageBox
      if ( Directory.Exists( inputTextBox.Text ) )
      {
         // add full path name to directoryTreeView 
         directoryTreeView.Nodes.Add( inputTextBox.Text );

         // insert subfolders
         PopulateTreeView( 
            inputTextBox.Text, directoryTreeView.Nodes[ 0 ] );
      } // end if
      // display error MessageBox if directory not found
      else
         MessageBox.Show( inputTextBox.Text + " could not be found.",
            "Directory Not Found", MessageBoxButtons.OK, 
            MessageBoxIcon.Error );
   } // end method enterButton_Click
} // end class TreeViewDirectoryStructureForm
