
/**
 * The Book class is to help staff keep track of store inventory.
 * 
 * @author Steffen L. Norgren, A00683006 
 * @version May 7, 2007
 */
public class Book
{
    private String title; // The book's title
    private String author; // The book's author
    private String publisher; // The book's publisher
    private int yearPublished; // The year the book was published
    private int quantityInStock; // The quantity of this book that is in stock
    private double purchasePrice; // The wholesale purchase price of the book
    private double salePrice; // the consumer sale price of the book
    private int quantityOnOrder; // quantity of the book on order
    private int quantitySold; // quantity of the book sold

    /**
     * The Book constructor allows for the input parameters of
     * title, author, publisher, year published and purchase price.
     * Quantity in stock and the selling price will be initialized
     * to zero.
     */
    public Book( String bookTitle, String bookAuthor, String bookPublisher,
                 int bookPublishYear, double bookPurchasePrice )
    {
        title = bookTitle;
        author = bookAuthor;
        publisher = bookPublisher;
        quantityInStock = 0;
        salePrice = 0.0;
        quantityOnOrder = 0;
        quantitySold = 0;
        
        // Check to see if a negative number is input
        if ( bookPublishYear < 0 )
        {
            // Sets the year published to a default value
            yearPublished = 2006;
        }
        else
        {
            // sets the year published to the input value
            yearPublished = bookPublishYear;
        }
        
        // Check to see if a negative number is input
        if ( bookPurchasePrice < 0 )
        {
            // Sets the purchase price to a default value
            purchasePrice = 0.0;
        }
        else
        {
            // sets the prurchase price to the input value
            purchasePrice = bookPurchasePrice;
        }
    }
    
    /**
     * This mutator method takes a parameter, restockAmount,
     * that specifies the number of books to add to inventory,
     * and increases quantity in stock by that number.
     */
    public void restock( int restockAmount )
    {
        // Check to see if the input is a valid number in this case
        if ( restockAmount < 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot have a negative value here.");
        }
        else
        {
            // Check to see if the number of books to be added to inventory
            // is greater than the number on order
            if ( restockAmount > quantityOnOrder )
            {
                // quantity in stock increased by the amount on order 
                quantityInStock += quantityOnOrder;
                
                // Tells the user that the book was only restocked by
                // a certain amount.
                System.out.println("Cannot restock for more than we have on order.\n" +
                                   "Quantity restocked by " + quantityOnOrder +
                                   ", the amount on order." );

                // Quantity on order set to zero as the restock amount
                // exceeds the amount on order, as we cannot have a
                // negative value here.
                quantityOnOrder = 0;
            }
            else
            {
                // Adds the number input by the user to the quantity in stock
                quantityInStock += restockAmount;
                
                // Quantity on order reduced by the restock amount
                quantityOnOrder -= restockAmount;
            } // end inner if
        } // end outer if
    }
    
    /**
     * This mutator method reduces quantity in stock by the 
     * number of books passed in through its parameter, sellAmount.
     */
    public void sell( int sellAmount )
    {
        // Check to see if the input is a valid number in this case
        if ( sellAmount < 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot have a negative value here.");
        }
        else
        {
            // Checks to see if the amount sold exceeds the amount in stock
            if ( ( quantityInStock - sellAmount ) < 0 )
            {
                System.out.println("I'm sorry, but you only have " + quantityInStock
                                   + " in stock.\nYou can sell a maximum of "
                                   + quantityInStock + " books.");
            }
            else
            {
                // check to see if the purchase price zero
                if ( purchasePrice == 0 )
                {
                    // inform the user that the purchase price is zero
                    System.out.println("Please set a purchase price that is not zero.");
                }
                else
                {
                    // check to see if the sale price is zero
                    if ( salePrice == 0 )
                    {
                        // inform the user that we don't give books away!!
                        System.out.println("You don't want to give books away for free! " +
                                           "Please set a purchase price that is not zero.");
                    }
                    else
                    {
                        // Subtracts the number input by the user to the quantity in stock
                        quantityInStock -= sellAmount;
                        
                        // Adds the number of books sold to quantity sold.
                        quantitySold += sellAmount;
                    }
                } // end innermost if
            } // end inner if
        } // end outer if
    }
    
    /**
     * Calculates and returns the profit from selling one copy of 
     * the book, based on the purchase price and selling price.
     */
    public double calcProfit()
    {
        // returns the profit from selling one copy of the book by
        // subtracting the sale price from the purchase price.
        return ( salePrice - purchasePrice );
    }
    
    /**
     * Calculates and returns the profit from all
     * the books that have been sold
     */
    public double calcTotalProfit()
    {
        // returns the result of calcProfit and multiplies it by the
        // amount of books sold
        return ( calcProfit() * quantitySold );
    }
    
    /**
     * Calculates and returns the current value of the quantity 
     * in stock, based on purchase price.
     */
    public double calcInventoryValue()
    {
        // returns the current value of the stock
        return ( purchasePrice * quantityInStock );
    }
    
    /**
     * This mutator method accepts the new purchase price as 
     * its parameter and changes the appropriate instance variable.
     */
    public void setPurchasePrice( double newPurchasePrice )
    {
        // Check to see if the input is a valid number in this case
        if ( newPurchasePrice < 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot enter a negative value here.");
        }
        else
        {
            // Sets the new purchase price
            purchasePrice = newPurchasePrice;
        }
    }
    
    /**
     * This mutator method accepts the new selling price as 
     * its parameter and changes the appropriate instance variable.
     */
    public void setSellingPrice( double newSalePrice )
    {
        // Check to see if the input is a valid number in this case
        if ( newSalePrice < 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot enter a negative value here.");
        }
        else
        {
            // Sets the new sale price
            salePrice = newSalePrice;
        }
    }
    
    /**
     * This mutator method passes in the quantity to order as a 
     * parameter and adds that value to the current quantity on order.
     */
    public void setQuantityOnOrder( int newQuantityOnOrder )
    {
        // Check to see if the input is a valid number in this case
        if ( newQuantityOnOrder < 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot have a negative value here.");
        }
        else
        {
            // Sets the new quantity on order
            quantityOnOrder = newQuantityOnOrder;
        }
    }
    
    /**
     * This method displays book information on the screen.
     */
    public void printDetails()
    {
        // Prints the book's details in the desired forumat
        System.out.println("Title: " + getTitle() );
        System.out.println("Author: " + getAuthor() );
        System.out.println("Publisher: " + getPublisher() );
        System.out.println("Year: " + getPublishYear() );
        System.out.println("Purchase price: $" + getPurchasePrice() );
        System.out.println("Selling price: $" + getSalePrice() );
        System.out.println("Quantity in stock: " + getQuantityInStock() );
        System.out.println("Quantity on order: " + getQuantityOnOrder() );
        System.out.println("Quantity sold: " + getQuantitySold() );
        System.out.println("Inventory value: $" + calcInventoryValue() );
        System.out.println("Profit on sales: $" + calcTotalProfit() );
    }
    
    /**
     * Getter for the book's title
     */
    public String getTitle()
    {
        // returns the book's title
        return title;
    }

    /**
     * Getter for the book's author
     */
    public String getAuthor()
    {
        // returns the book's author
        return author;
    }

    /**
     * Getter for the book's publisher
     */
    public String getPublisher()
    {
        // returns the book's publisher
        return publisher;
    }

    /**
     * Getter for the book's publish year
     */
    public int getPublishYear()
    {
        // returns the book's publish year
        return yearPublished;
    }

    /**
     * Getter for the book's quantity in stock
     */
    public int getQuantityInStock()
    {
        // returns the book's quantity in stock
        return quantityInStock;
    }

    /**
     * Getter for the book's purchase price
     */
    public double getPurchasePrice()
    {
        // returns the book's purchase price
        return purchasePrice;
    }

    /**
     * Getter for the book's sale price
     */
    public double getSalePrice()
    {
        // returns the book's sale price
        return salePrice;
    }

    /**
     * Getter for the book's quantity on order
     */
    public int getQuantityOnOrder()
    {
        // returns the book's quantity on order
        return quantityOnOrder;
    }

    /**
     * Getter for the book's quantity sold
     */
    public int getQuantitySold()
    {
        // returns the book's quantity sold
        return quantitySold;
    }
}