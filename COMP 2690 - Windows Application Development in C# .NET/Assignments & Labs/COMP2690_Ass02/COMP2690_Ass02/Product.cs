using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Ass02
{
    /// <summary>
    /// The Product class is a simple data class for holding and modifying
    /// product information.
    /// </summary>
    class Product
    {
        public enum Status
        {
            ForSale,
            Sold,
            Shipped
        };

        private string description; // product description
        private double price;       // product price in dollars and cents
        private Status status;      // product status as an enum of ForSale, Sold, Shipped

        /// <summary>
        /// Holds information about a product. This constructor assumes that the status
        /// for any products entered will be ForSale.
        /// </summary>
        /// <param name="description">Product description</param>
        /// <param name="price">Product price</param>
        public Product(string description, double price)
        {
            this.description = description;
            this.price = price;
            this.status = Status.ForSale;
        }

        /// <summary>
        /// Holds information about a product, however, this overloaded constructor
        /// allows for the input of the product status.
        /// </summary>
        /// <param name="description">Product description</param>
        /// <param name="price">Product price</param>
        /// <param name="status">Product status</param>
        public Product(string description, double price, Status status)
        {
            this.description = description;
            this.price = price;
            this.status = status;
        }

        /// <summary>
        /// Sells the product, but only if the status is currently ForSale,
        /// otherwise it will throw an exception.
        /// </summary>
        public void Sell()
        {
            try
            {
                // Checks to see if the product is currently ForSale, otherwise
                // it will produce an error.
                if (this.status == Status.ForSale)
                {
                    this.status = Status.Sold;
                }
                else
                {
                    // If the product status is not ForSale, produce an appropriate error message.
                    if (this.status == Status.Sold)
                    {
                        throw new ApplicationException("\nProduct already sold!");
                    }
                    else
                    {
                        throw new ApplicationException("\nProduct already shipped!");
                    }
                }
            }
            catch(Exception except)
            {
                // Write the errorr message to the console.
                Console.Write(except.Message);
                Console.ReadLine();
                Console.WriteLine();
            }
        }

        /// <summary>
        /// Ships the product, but only if the status is currently Sold,
        /// otherwise it will throw an exception.
        /// </summary>
        public void Ship()
        {
            try
            {
                // Checks to see if the product is currently Sold, otherwise
                // it will produce an error.
                if (this.status == Status.Sold)
                {
                    this.status = Status.Shipped;
                }
                else
                {
                    // If the product status is not Sold, produce an appropriate error message.
                    if (this.status == Status.ForSale)
                    {
                        throw new ApplicationException("\nProduct has not been sold!");
                    }
                    else
                    {
                        throw new ApplicationException("\nProduct already shipped!");
                    }
                }
            }
            catch(Exception except)
            {
                // Write the errorr message to the console.
                Console.Write(except.Message);
                Console.ReadLine();
                Console.WriteLine();
            }
        }

        /// <summary>
        /// Overridden ToString method returns information about the current
        /// Product object in the proper format.
        /// </summary>
        /// <returns>string representing the current product object</returns>
        public override string ToString()
        {
            return string.Format("{0}: {1} for {2:C}", status, description, price);
        }
    }
}
