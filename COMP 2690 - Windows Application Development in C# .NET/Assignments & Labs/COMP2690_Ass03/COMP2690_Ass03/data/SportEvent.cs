using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Ass03.data
{
    /// <summary>
    /// This class holds general information about sporting events.
    /// </summary>
    abstract class SportEvent
    {
        protected DateTime date;
        protected string opponent1;
        protected string opponent2;

        public SportEvent(String input)
        {
            string[] elements = input.Split(',');

            DateTime.TryParse(elements[1], out this.date);
            this.opponent1 = elements[2];
            this.opponent2 = elements[3];
        }

        /// <summary>
        /// A string representation of the hockey object.
        /// </summary>
        /// <returns>A string representing the hockey game in question.</returns>
        public override string ToString()
        {
            string returnString;

            returnString = string.Format("{0} vs. {1} on {2}", 
                opponent1, opponent2, date.ToShortDateString());

            return returnString;
        }
    }
}
