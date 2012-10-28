/*
 * FileWatcher.cs - Assignment One
 * 
 * Copyright (C) Steffen L. Norgren 2009 <ironix@trollop.org>
 *               A00683006
 *               
 * Created: 2009-06-22
 * 
 * FileWatcher.cs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FileWatcher.cs is distributed in the hope that it will be useful, but
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

namespace Assignment_One
{
    public partial class FileWatcher : Form
    {
        private EventController fileSystemEvents;

        /// <summary>
        /// Default contructor for the FileWatcher form
        /// </summary>
        public FileWatcher()
        {
            InitializeComponent();
            FileSystemEvents = new EventController();
        }

        /// <summary>
        /// Event handler for the stop button. Checks to see if the wathers are enabled
        /// before disabling this button and enabling the stop button.
        /// This also starts the timer.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
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

        /// <summary>
        /// Event handler for the stop button. Checks to see if the wathers are enabled
        /// before disabling this button and enabling the start button.
        /// This also stops the timer.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
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

        /// <summary>
        /// Event handler for the clear button, which simply clears the text box and list box.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
        private void btn_clear_Click(object sender, EventArgs e)
        {
            txtMonitor.Clear();
            lstNewFiles.Items.Clear();
        }

        /// <summary>
        /// Accessor for the EventController object
        /// </summary>
        private EventController FileSystemEvents
        {
            get { return fileSystemEvents; }
            set { fileSystemEvents = value; }
        }

        /// <summary>
        /// Event handler for when the application is closed and cleans up any open watchers.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
        private void FileWatcher_FormClosed(object sender, FormClosedEventArgs e)
        {
            FileSystemEvents.EnableWatchers(false);
            FileSystemEvents.DisposeWatchers();
        }

        /// <summary>
        /// The form's timer, which adds any new data into the text box and list box before
        /// clearing the source.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
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
