/*
 * EventController.cs - Assignment One
 * 
 * Copyright (C) Steffen L. Norgren 2009 <ironix@trollop.org>
 *               A00683006
 *               
 * Created: 2009-06-22
 * 
 * EventController.cs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * EventController.cs is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections;

namespace Assignment_One
{
    class EventController
    {
        private FileSystemWatcher firstWatcher;
        private FileSystemWatcher secondWatcher;
        private ArrayList newList;
        private String changed;

        /// <summary>
        /// Default constructor for the event controller
        /// </summary>
        public EventController() : this(@"C:\Upload", @"*.txt")
        {
        }

        /// <summary>
        /// Overloaded constructor, which allows custom watcher paths and filters.
        /// </summary>
        /// <param name="path">The string of the path to be watched</param>
        /// <param name="filter">Specific file matching</param>
        public EventController(String path, String filter)
        {
            FirstWatcher = new FileSystemWatcher(path, filter);
            SecondWatcher = new FileSystemWatcher(path, filter);

            FirstWatcher.IncludeSubdirectories = true;
            SecondWatcher.IncludeSubdirectories = true;
            EnableWatchers(false); // initially disable events

            NewList = new ArrayList();
        }

        /// <summary>
        /// Enables or disables the files system watchers and then
        /// enables the raising of events.
        /// </summary>
        /// <param name="enabled">true or false depending on whether to enable or disable</param>
        public void EnableWatchers(bool enabled)
        {
            if (enabled)
            {
                FirstWatcher.Changed += new FileSystemEventHandler(FirstWatcher_Changed);
                SecondWatcher.Created += new FileSystemEventHandler(SecondWatcher_Created);
                SecondWatcher.Deleted += new FileSystemEventHandler(SecondWatcher_Deleted);
            }

            FirstWatcher.EnableRaisingEvents = enabled;
            SecondWatcher.EnableRaisingEvents = enabled;
        }

        /// <summary>
        /// Event handler for catching any changes to the associated
        /// watched folders and files.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
        private void FirstWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            Changed += "- CHANGED -\r\n" + "Path: " + e.FullPath + "\r\n" +
                "Time Modified: " + DateTime.Now + "\r\n\r\n";
        }

        /// <summary>
        /// Event handler for catching any creations within the associated
        /// watched folders and files.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
        private void SecondWatcher_Created(object sender, FileSystemEventArgs e)
        {
            NewList.Add(e.Name);
            Changed += "- CREATED -\r\n" + "Path: " + e.FullPath + "\r\n" +
                "Time Modified: " + DateTime.Now + "\r\n\r\n";
        }

        /// <summary>
        /// Event handler for catching any deletions to the associated
        /// watched folders and files.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
        private void SecondWatcher_Deleted(object sender, FileSystemEventArgs e)
        {
            Changed += "- DELETED -\r\n" + "Path: " + e.FullPath + "\r\n" +
                "Time Modified: " + DateTime.Now + "\r\n\r\n";
        }

        /// <summary>
        /// Returns whether the watchers are raising events or not.
        /// </summary>
        /// <returns>True or false depending on if events are being raised or not</returns>
        public bool WatchersEnabled()
        {
            if (FirstWatcher.EnableRaisingEvents)
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// Disposes any current watchers.
        /// </summary>
        public void DisposeWatchers()
        {
            FirstWatcher.Dispose();
            SecondWatcher.Dispose();
        }

        /// <summary>
        /// Accessor for the first watcher
        /// </summary>
        private FileSystemWatcher FirstWatcher
        {
            get { return firstWatcher; }
            set { firstWatcher = value; }
        }

        /// <summary>
        /// Accessor for the second watcher
        /// </summary>
        private FileSystemWatcher SecondWatcher
        {
            get { return secondWatcher; }
            set { secondWatcher = value; }
        }

        /// <summary>
        /// Accessor for the array list of new filesystem items
        /// </summary>
        public ArrayList NewList
        {
            get { return newList; }
            set { newList = value; }
        }

        /// <summary>
        /// Accessor for the string of changed and deleted items
        /// </summary>
        public String Changed
        {
            get { return changed; }
            set { changed = value; }
        }
    }
}
