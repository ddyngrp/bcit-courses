
/**
 * Music class provides information about: title, artist, playing time, 
 * sound quality.
 * 
 * @author Colleen Penrowley 
 * @version comp 1451 Spring 2006
 */
public class Music
{
    private String title;
    private String artist;
    private double playingTime;
    private String soundQuality;

    /**
     * Constructor for objects of class Music
     */
    public Music(String title, String artist, double playingTime, String soundQuality)
    {
        this.title = title;
        this.artist = artist;
        this.playingTime = playingTime;
        this.soundQuality = soundQuality;
    
    }
    
    /**
     * @return the music title
     */
    public String getTitle()
    {
        return title;
    }
    
    /**
     * @return the music artist
     */
    public String getArtist()
    {
        return artist;
    }
    
    /**
     * @return the playing time of the music
     */
    public double getPlayingTime()
    {
        return playingTime;
    }
    
    /**
     * @return the music sound quality, e.g. "good", "fair"
     */
    public String getSoundQuality()
    {
        return soundQuality;
    }
    
    /**
     * @return a String representing this music
     */
    public String toString()
    {
        return "title: "+ title + "\n artist: " + artist + "\n time: " + playingTime + "\n sound: " + soundQuality;
    }
    
}
