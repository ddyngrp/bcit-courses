
/**
 * The Book class is to help staff keep track of store inventory.
 * 
 * @author Steffen L. Norgren, A00683006 
 * @version April 23, 2007
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
        yearPublished = bookPublishYear;
        quantityInStock = 0;
        purchasePrice = bookPurchasePrice;
        salePrice = 0;
    }
    
    /**
     * This mutator method takes a parameter, restockAmount,
     * that specifies the number of books to add to inventory,
     * and increases quantity in stock by that number.
     */
    public void restock( int restockAmount )
    {
        // Check to see if the input is a valid number in this case
        if ( restockAmount <= 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot have a negative value here.");
        }
        else
        {
            // Adds the number input by the user to the quantity in stock
            quantityInStock += restockAmount;
        }
    }
    
    /**
     * This mutator method reduces quantity in stock by the 
     * number of books passed in through its parameter, sellAmount.
     */
    public void sell( int sellAmount )
    {
        // Check to see if the input is a valid number in this case
        if ( sellAmount <= 0 )
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
                                   + " in stock.\n You can sell a maximum of "
                                   + quantityInStock + " books.");
            }
            else
            {
                // Subtracts the number input by the user to the quantity in stock
                quantityInStock -= sellAmount;
            }
        }
    }
    
    /**
     * This mutator method accepts the new purchase price as 
     * its parameter and changes the appropriate instance variable.
     */
    public void setPurchasePrice( double newPurchasePrice )
    {
        // Check to see if the input is a valid number in this case
        if ( newPurchasePrice <= 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot have a negative value here.");
        }
        else
        {
            // Adds the number input by the user to the quantity in stock
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
        if ( newSalePrice <= 0 )
        {
            // Inform the user that they entered an invalid number
            System.out.println("I'm sorry, but you cannot have a negative value here.");
        }
        else
        {
            // Adds the number input by the user to the quantity in stock
            salePrice = newSalePrice;
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
}