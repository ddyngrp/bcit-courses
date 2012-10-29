using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Midterm
{
    class GroceryItemCollection : List<GroceryItem>
    {
        public void PrintGroceryList()
        {
            Console.WriteLine("\n{0,-24} {1,6} {2,-18}", "Grocery Item", "Price", "  Expires");
            for (int i = 0; i < 55; i++)
            {
                Console.Write("=");
                if (i == 54)
                {
                    Console.WriteLine();
                }
            }

            foreach (GroceryItem item in this)
            {
                if (DateTime.MinValue.Equals(item.ExpirationDate))
                {
                    Console.WriteLine("{0,-24} {1,6} {2,-18}", item.Description, item.Price, "  <Never>");
                }
                else
                {
                    Console.WriteLine("{0,-24} {1,6} {2,-18:  ddd MMM dd, yyyy}", item.Description, item.Price, item.ExpirationDate);
                }
            }
        }
    }
}
