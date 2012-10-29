using System;
using System.Collections;
using System.Text;

namespace COMP2690_Ass03.data
{
    /// <summary>
    /// This class holds information relating to tennis matches.
    /// </summary>
    class Tennis : SportEvent
    {
        private ArrayList setList;

        /// <summary>
        /// Sets the values for the tennis object based on a comma deliminated
        /// string passed to the constructor.
        /// </summary>
        /// <param name="input">A string in the format of 
        /// "tennis,date,opponent1,opponent2,{set scores}"</param>
        public Tennis(string input) : base(input)
        {
            setList = new ArrayList();
            string[] elements = input.Split(',');

            // Add all the sets tot he setList ArrayList
            for (int i = 4; i < elements.Length; i++)
            {
                int tempInt;
                int.TryParse(elements[i], out tempInt);
                setList.Add(tempInt);
            }
        }

        /// <summary>
        /// Calculates who won each set and then tallies the set wins to calculate
        /// who won the entire match.
        /// </summary>
        /// <returns>A string representing each set score and the final match score.</returns>
        private string calculateSetWins()
        {
            string returnString = "";
            int setCount = 0;   // a running counter for the set
            int player1 = 0;    // player 1's set score
            int player2 = 0;    // player 2's set score
            int setWins1 = 0;   // the number of set wins for player 1
            int setWins2 = 0;   // the number of set wins for player 2

            foreach (int i in setList)
            {
                // Checking to see if a complete set has been iterated or not
                if (setCount % 2 == 0 || setCount == 0)
                {
                    player1 = i;    // setting the player's score for the current set.
                }
                else
                {
                    player2 = i;    // setting the player's score for the current set.

                    // Adding to the tally of set wins for each player
                    if (player1 > player2)
                    {
                        setWins1++;
                    }
                    else if (player2 > player1)
                    {
                        setWins2++;
                    }

                    returnString += string.Format("\n  Set {0}: {1}, {2}",
                        (setCount / 2) + 1, player1, player2);
                }
                setCount++;
            }

            // Calculate who won the entire tennis match
            if (setWins1 > setWins2)
            {
                returnString += string.Format("\n  {0} wins the match with {1} set wins to {2}!", 
                    opponent1, setWins1, setWins2);
            }
            else if (setWins2 > setWins1)
            {
                returnString += string.Format("\n  {0} wins the match with {1} set wins to {2}!", 
                    opponent2, setWins2, setWins1);
            }
            else
            {
                returnString += string.Format("\n  The match is a tie with {0} set wins to {1}!", 
                    setWins1, setWins2);
            }

            return returnString;
        }

        /// <summary>
        /// Creates a formatted string representation of the Tennis object.
        /// </summary>
        /// <returns>A string representation of the Tennis object.</returns>
        public override string ToString()
        {
            string returnString = base.ToString();

            returnString = string.Format("Tennis Match: " + base.ToString());
            returnString += calculateSetWins() + "\n";

            return returnString;
        }
    }
}
