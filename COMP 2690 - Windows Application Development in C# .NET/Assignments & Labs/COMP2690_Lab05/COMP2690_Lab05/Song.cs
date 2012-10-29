using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Lab05
{
    class Song
    {
        private string artist, title;
        private int lengthInSeconds, timesPlayed;

        public Song(string artist, string title, int length)
        {
            this.artist = artist;
            this.title = title;
            this.lengthInSeconds = length;
            this.timesPlayed = 0;
        }

        public void Play()
        {
            this.timesPlayed += 1;
        }

        public string Artist
        {
            get { return artist; }
        }

        public string Title
        {
            get { return title; }
        }

        public int LengthInSeconds
        {
            get { return lengthInSeconds; }
        }

        public int TimesPlayed
        {
            get { return timesPlayed; }
        }

        public override string ToString()
        {
            string returnString;

            returnString = String.Format("  {0}, {1}, {2} seconds", this.Artist, this.Title, this.LengthInSeconds);

            return returnString;
        }
    }
}
