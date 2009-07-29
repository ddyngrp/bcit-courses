/*
 * Explorer.cs - Assignment Two - Explorer Style Interface
 * 
 * Copyright (C) Steffen L. Norgren 2009 <ironix@trollop.org>
 *               A00683006
 *               
 * Created: 2009-07-06
 * 
 * Explorer.cs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Explorer.cs is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
        /// <summary>
        /// Default Constructor
        /// </summary>
        public Explorer()
        {
            InitializeComponent();
            InitDirectoryTree();
        }

        /// <summary>
        /// Populate the TreeView with drives that are in a "ready" state
        /// </summary>
        private void InitDirectoryTree()
        {
            // Don't draw the TreeView until finished
            treeView1.BeginUpdate();

            // Create and add the root nodes
            DriveInfo[] drives = DriveInfo.GetDrives();
            foreach (DriveInfo drive in drives)
            {
                if (drive.IsReady)
                {
                    TreeNode rootNode = new TreeNode(drive.Name);
                    treeView1.Nodes.Add(rootNode);
                    PopulateNode(rootNode);
                }
            }

            // Expand the first root node
            treeView1.Nodes[0].Expand();

            // Populate the ListView with the root node's files
            PopulateList(treeView1.Nodes[0]);

            // Update the TreeView
            treeView1.EndUpdate();
        }

        /// <summary>
        /// Populate a node with subnodes, i.e. subfolders
        /// </summary>
        /// <param name="dirNode">The node to be populated</param>
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

        /// <summary>
        /// Populate the ListView with the contents of a directory
        /// </summary>
        /// <param name="node">The node directory to lookup</param>
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

        /// <summary>
        /// Queries the system registry for a file extension and then
        /// retrieves the associated file type information.
        /// </summary>
        /// <param name="extension">The file extention to lookup</param>
        /// <returns>File type info</returns>
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

        /// <summary>
        /// Populates all subnodes with nodes before expanding the current node
        /// in order to accurately show which subnodes can be expanded.
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void treeView1_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            // Populate the subfolder nodes to a depth of 1
            foreach (TreeNode node in e.Node.Nodes)
            {
                // Only populate if empty
                if (node.Nodes.Count == 0)
                {
                    PopulateNode(node);
                }
            }
        }

        /// <summary>
        /// Event that is fired when a node is clicked. Due to some bugs with populating
        /// the ListView, this event is ignored.
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            // Using this event sometimes causes the listView to change when we
            // don't want it to. Using "BeforeSelect" instead.
        }

        /// <summary>
        /// Populates the ListView when a node selection has changed.
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void treeView1_BeforeSelect(object sender, TreeViewCancelEventArgs e)
        {
            // Only populate if empty
            PopulateList(e.Node);
        }
    }
}
