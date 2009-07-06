using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Microsoft.Win32; // Give access to the registry

namespace Explorer_Style_Interface
{
    public partial class Explorer : Form
    {
        public Explorer()
        {
            InitializeComponent();
            InitDirectoryTree(@"C:\");
        }

        private void InitDirectoryTree(String rootPath)
        {
            // Don't draw the TreeView until finished
            treeView1.BeginUpdate();

            // Create and add the root node
            TreeNode rootNode = new TreeNode(rootPath);
            treeView1.Nodes.Add(rootNode);

            // Populate the root node's folders
            PopulateNode(rootNode);
            treeView1.Nodes[0].Expand();

            // Populate the ListView with the root node's files
            PopulateList(rootNode);

            // Update the TreeView
            treeView1.EndUpdate();
        }

        private void PopulateNode(TreeNode dirNode)
        {
            DirectoryInfo dirInfo = new DirectoryInfo(dirNode.FullPath);

            // Avoid access errors
            try
            {
                foreach (DirectoryInfo dirItem in dirInfo.GetDirectories())
                {
                    // Don't display hidden directories
                    if ((dirItem.Attributes & FileAttributes.Hidden) != FileAttributes.Hidden)
                    {
                        TreeNode newNode = new TreeNode(dirItem.Name);

                        dirNode.Nodes.Add(newNode);

                        // To simplify things, collapse any expanded subnodes
                        if (dirNode.IsExpanded)
                        {
                            dirNode.Collapse();
                        }
                    }
                }
            }
            catch (Exception)
            {
            }
        }

        private void PopulateList(TreeNode node)
        {
            // Don't draw the listView until finished
            listView1.BeginUpdate();
            listView1.Items.Clear();

            DirectoryInfo dirInfo = new DirectoryInfo(node.FullPath);

            // First populate the ListView with subdirectories
            foreach (DirectoryInfo dir in dirInfo.GetDirectories())
            {
                // Don't process hidden directories
                if ((dir.Attributes & FileAttributes.Hidden) != FileAttributes.Hidden)
                {
                    ListViewItem listFileItem = new ListViewItem();
                    ListViewItem.ListViewSubItem fileType = new ListViewItem.ListViewSubItem();
                    ListViewItem.ListViewSubItem fileModified = new ListViewItem.ListViewSubItem();

                    listFileItem.Text = dir.Name;

                    fileType.Text = "Directory";
                    fileModified.Text = dir.LastWriteTime.ToString();

                    listFileItem.SubItems.Add(fileType);
                    listFileItem.SubItems.Add(fileModified);
                    listFileItem.ImageIndex = 0;
                    listView1.Items.Add(listFileItem);
                }
            }

            // Populate the ListView with files
            foreach (FileInfo file in dirInfo.GetFiles())
            {
                // Don't proces hidden files
                if ((file.Attributes & FileAttributes.Hidden) != FileAttributes.Hidden)
                {
                    ListViewItem listFileItem = new ListViewItem();
                    ListViewItem.ListViewSubItem fileType = new ListViewItem.ListViewSubItem();
                    ListViewItem.ListViewSubItem fileModified = new ListViewItem.ListViewSubItem();

                    listFileItem.Text = file.Name;

                    fileType.Text = GetFileType(file.Extension);
                    fileModified.Text = file.LastWriteTime.ToString();

                    listFileItem.SubItems.Add(fileType);
                    listFileItem.SubItems.Add(fileModified);
                    listFileItem.ImageIndex = 1;
                    listView1.Items.Add(listFileItem);
                }
            }

            if (dirInfo.GetFiles().Length > 0)
            {
                // Resize the columns based on the contents
                listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            }
            else
            {
                // Resize the ListView columns based on the header size
                listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
            }

            // Update the listView
            listView1.EndUpdate();
        }

        private String GetFileType(String extension)
        {
            // Create a registry key object to represent the HKEY_CLASSES_ROOT registry section
            RegistryKey rkRoot = Registry.ClassesRoot;

            // Attempt to retrieve the registry key for the file type
            RegistryKey rkFileType = rkRoot.OpenSubKey(extension);

            try
            {
                // Retrieve the file type key
                String fileType = (String)rkFileType.GetValue(null);

                // Open the file type description key
                RegistryKey rkApp = rkRoot.OpenSubKey(fileType);

                // Retrieve the file type description value
                String fileApp = (String)rkApp.GetValue(null);

                // Close registries
                rkFileType.Close();
                rkApp.Close();
                rkRoot.Close();

                return fileApp;
            }
            catch (Exception)
            {
                return extension;
            }
        }

        private void treeView1_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            // Populate the subfolder nodes to a depth of 1
            foreach (TreeNode node in e.Node.Nodes)
            {
                node.Nodes.Clear();
                PopulateNode(node);
            }
        }

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            // Populate the ListView with files
            PopulateList(e.Node);
        }
    }
}
