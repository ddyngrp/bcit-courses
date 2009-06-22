using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections;
using System.Windows.Forms;

namespace Assignment_One
{
    class EventController
    {
        private FileSystemWatcher firstWatcher;
        private FileSystemWatcher secondWatcher;
        private static ArrayList newList;
        private static String changed;

        /// <summary>
        /// Default constructor for the event controller
        /// </summary>
        public EventController() : this(@"C:\Upload", @"*.txt")
        {
        }

        public EventController(String path, String filter)
        {
            FirstWatcher = new FileSystemWatcher(path, filter);
            SecondWatcher = new FileSystemWatcher(path, filter);

            FirstWatcher.IncludeSubdirectories = true;
            SecondWatcher.IncludeSubdirectories = true;
            EnableWatchers(false); // initially disable events

            NewList = new ArrayList();
        }

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

        private static void FirstWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            changed += "- CHANGED -\r\n" + "Path: " + e.FullPath + "\r\n" +
                "Time Modified: " + DateTime.Now + "\r\n\r\n";
        }

        private static void SecondWatcher_Created(object sender, FileSystemEventArgs e)
        {
            newList.Add(e.Name);
            changed += "- CREATED -\r\n" + "Path: " + e.FullPath + "\r\n" +
                "Time Modified: " + DateTime.Now + "\r\n\r\n";
        }

        private static void SecondWatcher_Deleted(object sender, FileSystemEventArgs e)
        {
            changed += "- DELETED -\r\n" + "Path: " + e.FullPath + "\r\n" +
                "Time Modified: " + DateTime.Now + "\r\n\r\n";
        }

        public bool WatchersEnabled()
        {
            if (FirstWatcher.EnableRaisingEvents)
            {
                return true;
            }

            return false;
        }

        public void DisposeWatchers()
        {
            FirstWatcher.Dispose();
            SecondWatcher.Dispose();
        }

        private FileSystemWatcher FirstWatcher
        {
            get { return firstWatcher; }
            set { firstWatcher = value; }
        }

        private FileSystemWatcher SecondWatcher
        {
            get { return secondWatcher; }
            set { secondWatcher = value; }
        }

        public ArrayList NewList
        {
            get { return newList; }
            set { newList = value; }
        }

        public String Changed
        {
            get { return changed; }
            set { changed = value; }
        }
    }
}
