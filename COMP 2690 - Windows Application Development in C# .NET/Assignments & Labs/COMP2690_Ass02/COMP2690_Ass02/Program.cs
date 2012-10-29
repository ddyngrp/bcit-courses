using System;
using System.Collections;
using System.Text;

namespace COMP2690_Ass02
{
    /// <summary>
    /// The Program class is the driver that interfaces with the Product class and
    /// stores/prints created Product objects within an ArrayList. It also allows
    /// for the modification of individual products within the ArrayList.
    /// </summary>
    class Program
    {
        public enum Status
        {
            Sell,
            Ship
        };

        /// <summary>
        /// The main method is the driver for this program. It adds products
        /// to an ArrayList, modifies the entries, and prints them out.
        /// </summary>
        /// <param name="args">Command line arguments, which are not implemented</param>
        static void Main(string[] args)
        {
            // Create a fresh ArrayList
            ArrayList productList = new ArrayList();

            // Add the three products to the productList and display the contents.
            productList.Add(new Product("Green blouse", 69.99));
            productList.Add(new Product("Shampoo", 5.95));
            productList.Add(new Product("Cat food (10kg)", 32.00));
            display(productList);

            // Modifies the first product and displays the results.
            modifyProduct(productList, 0, Status.Sell);
            display(productList);

            // Modifies the second product and displays the results.
            modifyProduct(productList, 1, Status.Sell);
            display(productList);

            // Modifies the third product and displays the results.
            modifyProduct(productList, 1, Status.Ship);
            display(productList);

            writeText("Done.");
        }

        /// <summary>
        /// This method modifies a product within the productList ArrayList. It basically
        /// allows you to either sell or ship the product since all products are
        /// created as ForSale by default.
        /// </summary>
        /// <param name="productList">The ArrayList of products.</param>
        /// <param name="productNum">The entry in the productList to modify.</param>
        /// <param name="status">Either sell or ship the product.</param>
        private static void modifyProduct(ArrayList productList, int productNum, Status status)
        {
            // Check to see if the productList entry is out of bounds.
            if (productNum < productList.Count || productNum < 0)
            {
                // Sell or Ship the product based on the status parameter
                switch (status)
                {
                    case Status.Sell:
                        writeText("\nSelling product " + (productNum + 1) + "...");
                        ((Product)productList[productNum]).Sell();
                        break;
                    case Status.Ship:
                        writeText("\nShipping product " + (productNum + 1) + "...");
                        ((Product)productList[productNum]).Ship();
                        break;
                    default:
                        writeText("\nNo status change provided...");
                        break;
                }
            }
            else
            {
                // Display an error if the index is out of range
                writeText("\nIndex out of range...");
            }
        }

        /// <summary>
        /// Since the formatting after each line of printed text is fairly constant,
        /// this method was written to avoid too much repetition. Basically it will
        /// print out the string passed to it with appropriate formatting.
        /// </summary>
        /// <param name="text">The text to be written to the console</param>
        private static void writeText(string text)
        {
            Console.Write(text);
            Console.ReadLine();
            Console.WriteLine();
        }

        /// <summary>
        /// This method cycles through each product object within the productList
        /// ArrayList and prints out the results.
        /// </summary>
        /// <param name="productList">The ArrayList to be written to the console</param>
        private static void display(ArrayList productList)
        {
            // Iterate through each Product object in the productList
            foreach (Product product in productList)
            {
                Console.WriteLine(product);
            }
            Console.WriteLine();
        }
    }
}
