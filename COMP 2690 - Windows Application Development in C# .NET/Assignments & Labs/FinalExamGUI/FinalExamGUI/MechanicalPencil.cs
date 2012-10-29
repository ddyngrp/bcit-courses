using System;
using System.Collections.Generic;
using System.Text;
using FinalExam;

namespace FinalExamGUI
{
    public class MechanicalPencil : Pencil
    {
        private string colour;
        private string leadType;
        private int leadCapacity;

        public MechanicalPencil(string colour, string leadType, int leadCapacity)
            : base(colour, leadType)
        {
            this.colour = colour;
            this.leadType = leadType;
            this.leadCapacity = leadCapacity;
        }

        public int LeadCapacity
        {
            get { return this.leadCapacity; }
            set
            {
                if (leadCapacity <= 0)
                {
                    throw new LeadCapacityException(this.leadCapacity);
                }
                else
                {
                    this.leadCapacity = value;
                }
            }
        }

        public override string ToString()
        {
            return "Mechanical pencil: " + this.colour;
        }
    }
}
