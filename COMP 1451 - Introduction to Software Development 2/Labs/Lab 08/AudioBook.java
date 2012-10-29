
/**
 * AudioBook class maintains information about a book presented in audio format:
 * title, author, publisher, playing time, sound quality
 * 
 * @author Colleen Penrowley 
 * @version comp 1451 Spring 2006
 */
public class AudioBook
{
	private double playingTime;
	private String author;
	private String publisher;
	private String title;
	private String soundQuality;

	/**
	 * Constructor for objects of class AudioBook
	 */
	public AudioBook(String title, String author, String publisher, double playingTime, String soundQuality)
	{
		this.title = title;
		this.author = author;
		this.publisher = publisher;
		this.playingTime = playingTime;
		this.soundQuality = soundQuality;	
	}

	/**
	 * @return the book title
	 */
	public String getTitle()
	{
	    return title;
	}
	
	/**
	 * @return the book author
	 */
	public String getAuthor()
	{
	    return author;
	}
	
	/**
	 * @treturn the book publisher
	 */
	public String getPublisher()
	{
	    return publisher;
	}
	
	/**
	 * @return the book's playing time
	 */
	public double getPlayingTime()
	{
	    return playingTime;
	}

	/**
	 * @return the book's sound quality, e.g. "good", "excellent"
	 */
	public String getSoundQuality()
	{
	    return soundQuality;
	}
	
	/**
	 * @return a String representing this book
	 */
	public String toString()
	{
	    return "title: " + title + "\n author: " + author + "\n publisher: " + publisher + "\n time: " + playingTime + "\n sound: " + soundQuality;
	}
}
