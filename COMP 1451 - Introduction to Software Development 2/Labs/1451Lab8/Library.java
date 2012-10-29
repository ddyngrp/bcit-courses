import java.util.ArrayList;
import java.util.Iterator;

/**
 * The Library class provides storage for several different kinds of library items.
 * 
 * @author Colleen Penrowley
 * @version comp 1451 Spring 2006
 */
public class Library
{
	private ArrayList<PrintedBook> printedBooks;
	private ArrayList<AudioBook> audioBooks;
	private ArrayList<Movie> movies;
	private ArrayList<Music> music;

	/**
	 * Constructor for objects of class Library
	 */
	public Library()
	{
		printedBooks = new ArrayList<PrintedBook>();
		audioBooks = new ArrayList<AudioBook>();
		movies = new ArrayList<Movie>();
		music = new ArrayList<Music>();
	}

	/**
	 * Show details of all the items in the library
	 */
	public void showAllItems()
	{
	    Iterator iter = printedBooks.iterator();
	    while (iter.hasNext()) {
	        System.out.println(iter.next());
	    }
	    
	    iter = audioBooks.iterator();
	    while (iter.hasNext()) {
	        System.out.println(iter.next());
	    }
	    
	    iter = movies.iterator();
	    while (iter.hasNext()) {
	        System.out.println(iter.next());
	    }
	    
	    iter = music.iterator();
	    while (iter.hasNext()) {
	        System.out.println(iter.next());
	    }
	}
	
	/**
	 * Add a printed book to the library
	 */
	public void addPrintedBook(PrintedBook book)
	{
	    printedBooks.add(book);
	}
	
	/**
	 * Add an audio book to the library
	 */
	public void addAudioBook(AudioBook book)
	{
	    audioBooks.add(book);
	}
	
	/**
	 * Add a movie to the library
	 */
	public void addMovie(Movie movie)
	{
	    movies.add(movie);
	}
	
	/**
	 * Add music to the library
	 */
	public void addMusic(Music musicItem)
	{
	    music.add(musicItem);
	}
}
