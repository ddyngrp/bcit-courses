
/**
 * Movie class maintains information about movies: title, director, 
 * playing time and sound quality
 * 
 * @author Colleen Penrowley 
 * @version comp 1451 Spring 2006
 */
public class Movie
{
    private String title;
    private String director;
    private double playingTime;
    private String soundQuality;

    /**
     * Constructor for objects of class Movie
     */
    public Movie(String title, String director, double playingTime, String soundQuality)
    {
        this.title = title;
        this.director = director;
        this.playingTime = playingTime;
        this.soundQuality = soundQuality;
    }

    /**
     * @return the movie's title
     */
    public String getTitle()
    {
        return title;
    }
    
    /**
     * @return the movie's director
     */
    public String getDirector()
    {
        return director;
    }
    
    /**
     * @return the movie's playing time
     */
    public double getPlayingTime()
    {
        return playingTime;
    }
    
    /**
     * @return the movie's sound quality, e.g. "good", "fair"
     */
    public String getSoundQuality()
    {
        return soundQuality;
    }
    
    /**
     * @return a String representing this movie
     */
    public String toString()
    {
        return "title: " +title + "\n director: " + director + "\n time: " + playingTime + "\n sound: " + soundQuality;
    }
    
}
