using System;
using System.Collections.Generic;
using System.Text;

namespace FinalExamGUI
{
    class LeadCapacityException : ApplicationException
    {
        private int leadCapacity;

        public LeadCapacityException(int leadCapacity)
            : base(string.Format("Lead capacity must be greater than 0."))
        {
            this.leadCapacity = leadCapacity;
        }

        public int LeadCapacity
        {
            get { return this.leadCapacity; }
        }
    }
}
