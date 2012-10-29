using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace XMLdotNET.XMLHotDOM
{
    public partial class TestHotDOM : Form
    {
        private XmlHotDocument m_hotDocument;
        
        public TestHotDOM()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }
        private void Form1_Load(object sender, System.EventArgs e)
        {
            PendingChanges.Text = "No pending changes.";
        }

        private void CloseForm(object sender, EventArgs e)
        {
            if (m_hotDocument != null)
                m_hotDocument.EnableFileChanges = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            m_hotDocument = new XmlHotDocument();
            m_hotDocument.UnderlyingDocumentChanged += new EventHandler(FileChanged);
            m_hotDocument.Load("HotDOMData.xml");
            m_hotDocument.EnableFileChanges = true;

            // Update UI
            UpdateUI();
        }
        private void FileChanged(object sender, EventArgs e)
        {
            // Update UI
            UpdateUI();
        }

        private void UpdateUI()
        {
            PendingChanges.Text = "No pending changes.";
            if (m_hotDocument.HasChanges)
                PendingChanges.Text = "*** Pending changes ***";

            OutputBox.Text = m_hotDocument.OuterXml;
        }
    }
}