using System;
using System.Collections.Generic;
using System.Text;
using FinalExam;

namespace FinalExamGUI
{
    class WritingUtensilCollection : List<WritingUtensil>
    {
        public int GetColourCount(String colour)
        {
            int colourCount = 0;

            foreach (WritingUtensil writingimplement in this)
            {
                if (writingimplement.Color.ToLower().Equals(colour.ToLower()))
                {
                    colourCount++;
                }
            }

            return colourCount;
        }
    }
}
