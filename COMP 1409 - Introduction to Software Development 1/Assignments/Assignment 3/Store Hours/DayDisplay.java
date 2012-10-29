
/**
 * The DayDisplay class maintains day information.
 * 
 * @author Steffen L. Norgren 
 * @version May 21, 2007
 */
public class DayDisplay
{
    private int dayOfWeek;
    
    /**
     * Constructor for DayDisplay objects. This constructor
     * sets a new day set at 0 (Sunday).
     */
    public DayDisplay()
    {
        dayOfWeek = 0;
    }
    
    /**
     * This method returns the numeric value of 
     * the current day.
     */
    public int getValue()
    {
        return dayOfWeek;
    }
    
    /**
     * This method returns the string representation of 
     * the day passed in as its parameter.
     */
    public String getDisplayValue(int whichDay)
    {
        // variable for the day name to be returned
        String dayName;
        
        // Switch statement to translate the value of the dayOfWeek
        // to an actual named day.
        switch ( whichDay )
        {
            case 0:
                dayName = "Sunday";
                break;
            case 1:
                dayName = "Monday";
                break;
            case 2:
                dayName = "Tuesday";
                break;
            case 3:
                dayName = "Wednesday";
                break;
            case 4:
                dayName = "Thursday";
                break;
            case 5:
                dayName = "Friday";
                break;
            case 6:
                dayName = "Saturday";
                break;
            default:
                dayName = "Invalid Day!";
                break;
        }
        
        return dayName;
    }
    
    /**
     * This method sets the day value to the new value. 
     * If the new value is less than zero or over the 
     * number of days per week, do nothing.
     */
    public void setValue(int newValue)
    {
        dayOfWeek = newValue;
    }
    
    /**
     * This method increments the day by one, rolling 
     * over to zero if the limit (days per week) is reached.
     */
    public void increment()
    {
        // Check to see if the day of the week is Saturday (6)
        // and sets it to 0 (Sunday). Otherwise just adds one day.
        if ( dayOfWeek == 6 )
        {
            dayOfWeek = 0;
        }
        else
        {
            dayOfWeek += 1;
        }
    }
}
