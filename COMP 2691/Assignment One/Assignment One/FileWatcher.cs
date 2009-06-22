using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Assignment_One
{
    public partial class FileWatcher : Form
    {
        private EventController fileSystemEvents;

        public FileWatcher()
        {
            InitializeComponent();
            FileSystemEvents = new EventController();
        }

        private void btn_start_Click(object sender, EventArgs e)
        {
            if (!FileSystemEvents.WatchersEnabled())
            {
                FileSystemEvents.EnableWatchers(true);
                btn_start.Enabled = false;
                btn_stop.Enabled = true;
                timer.Start();
            }
        }

        private void btn_stop_Click(object sender, EventArgs e)
        {
            if (FileSystemEvents.WatchersEnabled())
            {
                FileSystemEvents.EnableWatchers(false);
                btn_start.Enabled = true;
                btn_stop.Enabled = false;
                timer.Stop();
            }
        }

        private void btn_clear_Click(object sender, EventArgs e)
        {
            txtMonitor.Clear();
            lstNewFiles.Items.Clear();
        }

        private EventController FileSystemEvents
        {
            get { return fileSystemEvents; }
            set { fileSystemEvents = value; }
        }

        private void FileWatcher_FormClosed(object sender, FormClosedEventArgs e)
        {
            FileSystemEvents.EnableWatchers(false);
            FileSystemEvents.DisposeWatchers();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if (FileSystemEvents.NewList.Count > 0)
            {
                foreach (String s in FileSystemEvents.NewList)
                {
                    lstNewFiles.Items.Add(s);
                }
                FileSystemEvents.NewList.Clear();
            }

            if (FileSystemEvents.Changed != null)
            {
                txtMonitor.AppendText(FileSystemEvents.Changed.ToString());
                FileSystemEvents.Changed = null;
            }
        }
    }
}
