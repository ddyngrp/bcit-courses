using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Midterm
{
    class Program
    {
        private GroceryItemCollection groceryList;

        static void Main(string[] args)
        {
            Program midterm = new Program();
            midterm.groceryList.PrintGroceryList();
            Console.ReadLine(); // pause the program
        }

        public Program()
        {
            AddGroceryItems();
        }

        private void AddGroceryItems()
        {
            groceryList = new GroceryItemCollection();

            groceryList.Add(new GroceryItem("4L Milk", 3.87m, new DateTime(2006, 05, 25)));
            groceryList.Add(new GroceryItem("500g Cottage Cheese", 4.28m, new DateTime(2006, 06, 13)));
            groceryList.Add(new GroceryItem("1 Tin Mushroom Soup", 0.99m, new DateTime()));
            groceryList.Add(new GroceryItem("15kg Dog Food", 29.99m, new DateTime(2020, 01, 01)));
        }
    }
}
