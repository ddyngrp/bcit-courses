using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Midterm
{
    class GroceryItem
    {
        private string description;
        private decimal price;
        private DateTime expirationDate;

        public GroceryItem(string description, decimal price, DateTime expirationDate)
        {
            this.description = description;
            this.price = price;
            this.expirationDate = expirationDate;
        }

        public string Description
        {
            get { return description; }
        }

        public decimal Price
        {
            get { return price; }
            set { this.price = value; }
        }

        public DateTime ExpirationDate
        {
            get { return expirationDate; }
        }
    }
}
