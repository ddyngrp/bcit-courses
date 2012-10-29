using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Ass03.data
{
    /// <summary>
    /// This class holds information relating to hockey games.
    /// </summary>
    class Hockey : SportEvent
    {
        private int team1Score;
        private int team2Score;

        /// <summary>
        /// Sets the values for the hockey object based on a comma deliminated
        /// string passed to the constructor.
        /// </summary>
        /// <param name="input">A string in the format of 
        /// "hockey,date,team1,team2,team1Score, team2Score"</param>
        public Hockey(string input) : base(input)
        {
            string[] elements = input.Split(',');

            int.TryParse(elements[4], out team1Score);
            int.TryParse(elements[5], out team2Score);
        }

        /// <summary>
        /// Calculates which team has won (or tied) based on the score.
        /// </summary>
        /// <returns>A string describing which ream that won, or the tie.</returns>
        private string calculateWin()
        {
            string returnString;

            if (team1Score > team2Score)
            {
                returnString = string.Format("\n  {0} wins the game with a score of {1} to {2}!",
                    opponent1, team1Score, team2Score);
            }
            else if (team2Score > team1Score)
            {
                returnString = string.Format("\n  {0} wins the game with a score of {1} to {2}!",
                    opponent1, team1Score, team2Score);
            }
            else
            {
                returnString = string.Format("\n  The game ended in a tie with a score of {0} to {1}!",
                    team1Score, team2Score);
            }

            return returnString;
        }

        /// <summary>
        /// A string representation of the hockey object.
        /// </summary>
        /// <returns>A string representing the hockey game in question.</returns>
        public override string ToString()
        {
            string returnString;

            returnString = string.Format("Hockey Game: " + base.ToString());
            returnString += calculateWin() + "\n";

            return returnString;
        }
    }
}
