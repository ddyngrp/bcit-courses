using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Lab05
{
    class SongCollection : List<Song>
    {
        public int PlayedCount
        {
            get
            {
                int playedCount = 0;

                foreach (Song song in this)
                {
                    if (song.TimesPlayed > 0)
                    {
                        playedCount++;
                    }
                }

                return playedCount;
            }
        }

        public int TotalLength
        {
            get
            {
                int totalLength = 0;

                foreach (Song song in this)
                {
                    totalLength += song.LengthInSeconds;
                }

                return totalLength;
            }
        }

        public SongCollection GetAllByArtist(string artist)
        {
            SongCollection tempSongs = new SongCollection();

            foreach (Song song in this)
            {
                if (song.Artist.ToLower().Contains((artist.ToLower())))
                {
                    tempSongs.Add(song);
                }
            }

            return tempSongs;
        }
    }
}
