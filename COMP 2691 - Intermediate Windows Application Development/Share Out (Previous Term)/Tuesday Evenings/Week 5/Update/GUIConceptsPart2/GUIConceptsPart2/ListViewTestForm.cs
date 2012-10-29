
// Displaying directories and their contents in ListView.
using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

// Form contains a ListView which displays
// folders and files in a directory
public partial class ListViewTestForm : Form
{
   // store current directory
   string currentDirectory = Directory.GetCurrentDirectory();

   // default constructor
   public ListViewTestForm()
   {
      InitializeComponent();
   } // end constructor

   // browse directory user clicked or go up one level
   private void browserListView_Click( object sender, EventArgs e )
   {
      // ensure an item is selected
      if ( browserListView.SelectedItems.Count != 0 )
      {
         // if first item selected, go up one level
         if ( browserListView.Items[0].Selected )
         {
            // create DirectoryInfo object for directory
            DirectoryInfo directoryObject =
               new DirectoryInfo( currentDirectory );

            // if directory has parent, load it
            if ( directoryObject.Parent != null )
               LoadFilesInDirectory( directoryObject.Parent.FullName );
         } // end if

         // selected directory or file
         else
         {
            // directory or file chosen
            string chosen = browserListView.SelectedItems[ 0 ].Text;

            // if item selected is directory, load selected directory
            if ( Directory.Exists( currentDirectory + @"\" + chosen ) )
            {
               // if currently in C:\, do not need '\'; otherwise we do
               if ( currentDirectory == @"C:\" )
                  LoadFilesInDirectory( currentDirectory + chosen );
               else
                  LoadFilesInDirectory( 
                     currentDirectory + @"\" + chosen );
            } // end if
         } // end else

         // update displayLabel
         displayLabel.Text = currentDirectory;
      } // end if
   } // end method browserListView_Click

   // display files/subdirectories of current directory
   public void LoadFilesInDirectory( string currentDirectoryValue )
   {
      // load directory information and display
      try
      {
         // clear ListView and set first item
         browserListView.Items.Clear();
         browserListView.Items.Add( "Go Up One Level" );

         // update current directory
         currentDirectory = currentDirectoryValue;
         DirectoryInfo newCurrentDirectory =
            new DirectoryInfo( currentDirectory );

         // put files and directories into arrays
         DirectoryInfo[] directoryArray = 
            newCurrentDirectory.GetDirectories();
         FileInfo[] fileArray = newCurrentDirectory.GetFiles();

         // add directory names to ListView
         foreach ( DirectoryInfo dir in directoryArray )
         {
            // add directory to ListView
            ListViewItem newDirectoryItem =
               browserListView.Items.Add( dir.Name );

            newDirectoryItem.ImageIndex = 0;  // set directory image
         } // end foreach

         // add file names to ListView
         foreach ( FileInfo file in fileArray )
         {
            // add file to ListView
            ListViewItem newFileItem =
               browserListView.Items.Add( file.Name );

            newFileItem.ImageIndex = 1;  // set file image
         } // end foreach
      } // end try

      // access denied
      catch ( UnauthorizedAccessException )
      {
         MessageBox.Show( "Warning: Some fields may not be " +
            "visible due to permission settings",
            "Attention", 0, MessageBoxIcon.Warning );
      } // end catch
   } // end method LoadFilesInDirectory

   // handle load event when Form displayed for first time
   private void ListViewTestForm_Load( object sender, EventArgs e )
   {
      // set Image list
      Image folderImage = Image.FromFile(
         currentDirectory + @"\images\folder.bmp" );

      Image fileImage = Image.FromFile(
         currentDirectory + @"\images\file.bmp" );

      fileFolder.Images.Add( folderImage );
      fileFolder.Images.Add( fileImage );

      // load current directory into browserListView
      LoadFilesInDirectory( currentDirectory );
      displayLabel.Text = currentDirectory;
   } // end method ListViewTestForm_Load
} // end class ListViewTestForm

