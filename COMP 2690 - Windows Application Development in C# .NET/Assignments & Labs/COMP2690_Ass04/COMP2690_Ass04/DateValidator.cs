using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Ass04
{
    /// <summary>
    /// This class checks whether any partuclar date is valid or not.
    /// </summary>
    class DateValidator
    {
        /// <summary>
        /// Returns a true or false depending on whether the date input
        /// is valid or not.
        /// </summary>
        /// <param name="year">Input Year</param>
        /// <param name="month">Input Month</param>
        /// <param name="day">Input Day</param>
        /// <returns>True or False depending on whethe date is valid.</returns>
        public static bool Validate(string year, string month, string day)
        {
            int yearInt, monthInt, dayInt;

            if (int.TryParse(year, out yearInt)
                && int.TryParse(month, out monthInt)
                && int.TryParse(day, out dayInt))
            {
                try
                {
                    DateTime theDate = new DateTime(yearInt, monthInt, dayInt);
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
}
