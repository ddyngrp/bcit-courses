using System;
using System.Collections.Generic;
using System.Text;

using System.Xml;
using System.IO;

namespace XMLdotNET.XMLHotDOM
{
    #region XmlHotDocument Class
    public class XmlHotDocument : XmlDocument
    {
        #region Constructor
        // ************************************************
        // Class constructor
        public XmlHotDocument()
            : base()
        {
            m_watcher = new FileSystemWatcher();
            HasChanges = false;
            EnableFileChanges = false;
        }
        // ************************************************
        #endregion

        #region Events
        // ************************************************
        // EVENT: UnderlyingDocumentChanged 
        public event EventHandler UnderlyingDocumentChanged;
        // ************************************************
        #endregion

        #region Properties
        // ************************************************
        // PROPERTY: HasChanges 
        public bool HasChanges;
        // ************************************************

        // ************************************************
        // PROPERTY: EnableFileChanges 
        public bool EnableFileChanges
        {
            get
            {
                return m_watcher.EnableRaisingEvents;
            }

            set
            {
                if (value == true)
                {
                    // Set the path to watch for
                    string filename = m_filename;
                    FileInfo fi = new FileInfo(filename);
                    m_watcher.Path = fi.DirectoryName;
                    m_watcher.Filter = fi.Name;

                    // Set hooks for writing changes
                    m_watcher.NotifyFilter = NotifyFilters.LastWrite;
                    m_watcher.Changed += new FileSystemEventHandler(this.OnChanged);

                    // Start getting notifications
                    m_watcher.EnableRaisingEvents = true;
                }
                else
                    m_watcher.EnableRaisingEvents = false;
            }
        }
        // ************************************************
        #endregion

        #region Internal Properties
        private FileSystemWatcher m_watcher;
        private string m_filename;
        #endregion

        #region Method Overrides
        // ***************************************************
        // Do something special when loading from a file name
        public override void Load(string filename)
        {
            // Load the DOM the usual way
            m_filename = filename;
            base.Load(filename);  // XmlHotDocument : XmlDocument

            // Reset pending changes
            HasChanges = false;
        }
        // ***************************************************


        // ***************************************************
        // Define the internal event handlers
        private void OnChanged(object source, FileSystemEventArgs e)
        {
            HasChanges = true;
            if (UnderlyingDocumentChanged != null)
                UnderlyingDocumentChanged(this, EventArgs.Empty);
        }
        // ***************************************************
        #endregion

    }
    #endregion
}
