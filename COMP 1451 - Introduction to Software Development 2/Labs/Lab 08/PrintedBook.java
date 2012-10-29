
/**
 * PrintedBook class maintains information about a book presented in printed format:
 * title, author, publisher, number of pages.
 * 
 * @author Colleen Penrowley 
 * @version comp 1451 Spring 2006
 */
public class PrintedBook
{
    private String title;
    private String author;
    private String publisher;
    private int numberPages;

    /**
     * Constructor for objects of class PrintedBook
     */
    public PrintedBook(String title, String author, String publisher, int numberPages)
    {
       this.title = title;
       this.author = author;
       this.publisher = publisher;
       this.numberPages = numberPages;
        
    }
    
    /**
     * @return the book's title
     */
    public String getTitle()
    {
        return title;
    }
    
    /**
     * @return the book's author 
     */
    public String getAuthor()
    {
        return author;
    }
    
    /**
     * @return the book's publisher
     */
    public String getPublisher()
    {
        return publisher;
    }
    
    /**
     * @return the number of pages in the book
     */
    public int getNumberPages()
    {
        return numberPages;
    }
    
    /**
     * @return a String representing this book
     */
    public String toString()
    {
       return "title: " + title + "\n author: " + author + "\n publisher: " + publisher + "\n pages: " + numberPages;
    }

}
