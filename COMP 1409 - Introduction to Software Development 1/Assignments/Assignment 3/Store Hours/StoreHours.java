
/**
 * StoreHours maintains information about 
 * a store's open hours and days
 * 
 * @author Steffen L. Norgren 
 * @version May 21, 2007
 */

public class StoreHours
{
    public static final int CLOSED_DAY = 2; // Tuesday (Sunday = 0)
    public static final String OPENING_TIME = "09:00"; // store's opening time
    public static final String CLOSING_TIME = "17:00"; // store's closing time
    public static final String DAY_CYCLE_TIME = "23:59"; // time after which the
                                                         // incremented

    private ClockDisplay clock; // maintains the time information
    private DayDisplay day; // maintains day information
    private boolean isOpen; // whether store is open or closed
    private int numberToAdd = 1; // number to add to the current day when calculating
                             // when the next open date occurs
    private String openStatus; // the string data for open status
    private String appendClosedDay = ""; // string to append at the end of the returned
                                         // getCurrentTimeDay method
                                         // initialized to may compiler happy
    /**
     * Constructor for StoreHours objects
     */
    public StoreHours()
    {
        clock = new ClockDisplay();
        day = new DayDisplay();
    }
    
    /**
     * This method checks the open status of the store at the 
     * current time and day. If the store is open, it displays 
     * a "store open" message and the current time and day. If 
     * the store is closed, it displays a "store closed" message, 
     * the current time and day, and the time and day when the 
     * store will next be open.
     */
    public void checkStatus()
    {
        // runs the manageOpeningClosing method to update the current status
        manageOpeningClosing();
        
        if ( isOpen )
        {
            // runs the getOpenStatus to display the current status
            System.out.println( getOpenStatus() );
            
            // runs the getCurrentTimeDay method to display the current
            // time and day
            System.out.println( getCurrentTimeDay() );
        }
        else
        {
            // runs the getOpenStatus method to display the current status
            System.out.println( getOpenStatus() );
            
            // runs the getCurrentTimeDay method to display the current
            // time and day
            System.out.println( getCurrentTimeDay() );
                      
            // checks to see if the next day is a closed day and adjusts
            // the number to add accodringly
            if ( day.getValue() + numberToAdd == CLOSED_DAY )
            {
                numberToAdd = 2;
            }
            // if today is a Saturday (day 6) then the next day has to be
            // set to 0, so we simply set the number to add to be today's number
            // but a negative such that when it is added we get 0.
            else if ( day.getValue() == 6 )
            {
                numberToAdd = ( day.getValue() * -1 );
            }
            // if the store will be open today set the number to add to 0
            // since the store will be opon on the current day
            else if ( clock.getTime().compareTo( OPENING_TIME ) < 0 
                      && day.getValue() != CLOSED_DAY)
            {
                numberToAdd = 0;
            }
            else
            {
                numberToAdd = 1;
            } // end inner if

            System.out.println( "Opening time is " + OPENING_TIME + " "
                                + day.getDisplayValue( day.getValue() + numberToAdd ) );
        } // end if
    }
    
    /**
     * This method increments the time by one minute. It ensures 
     * that the day is kept in synch, i.e. if the clock reaches 
     * midnight it increments the day. It also invokes 
     * manageOpeningClosing() to ensure that the store opening 
     * is kept in synch with the time and day.
     */
    public void increment()
    {
        // checks to see if the day needs to be incremented after the next
        // minute incrementation
        if ( clock.getTime().compareTo( DAY_CYCLE_TIME ) == 0 )
        {
            // runs the ClockDisplay timeTick method to increment the time by one minute
            clock.timeTick();
            
            // runs the DayDisplay increment method to increment the day by one
            day.increment();
        }
        else
        {
            // runs the ClockDisplay timeTick method to increment the time by one minute
            clock.timeTick();
        }
    }
    
    /**
     * This method sets a new time and day. 
     * It is useful for testing the program. 
     */
    public void setTimeAndDay(int newHour, int newMinute, 
                              int newDay)
    {
        // checks to see if the input is valid
        if ( newHour > 24 || newDay > 6 )
        {
            System.out.println( "Invalid input. Minutes must be from 0-60, hours from 0-24\n" +
                                "and days must be from 0-6" );
        }
        else
        {
            // implements the setTime method in the ClockDisplay class
            clock.setTime( newHour, newMinute );
        
            // implements the setDate method in the DayDisplay class
            day.setValue( newDay );
        }
    }
    
    /**
     * This method advances the clock (and potentially day) by 
     * the number of minutes passed in through the parameter. 
     * It is useful for testing the program.
     */
    public void advanceMinutes(int minutesToAdvance)
    {
        // validates that the input is not negative
        if ( minutesToAdvance < 0 )
        {
            System.out.println("Please input a positive number.");
        }
        else
        {
            // a  loop that implements the increment method
            // until t reaches one less than minutesToAdvance
            for ( int t = 0; t < minutesToAdvance; t++ )
            {
                increment();
            }
        }
    }
    
    /**
     * This method manages the opening and closing of the store. 
     * If it is time to open, the store is opened. If it is time 
     * to close, the store is closed.
     */
    private void manageOpeningClosing()
    {
        // checks to see if the store should be open by comparing
        // the time strings lexicographically whereby the lexographic
        // value of 09:00 is less than the lexographic value of 09:01.
        if ( clock.getTime().compareTo( OPENING_TIME ) >= 0 && 
             clock.getTime().compareTo( CLOSING_TIME ) < 0 && 
             day.getValue() != CLOSED_DAY )
        {
            // implements the open method
            open();
        }
        else
        {
            // implements the close method
            close();
        }
    }
    
    /**
     * This method opens the store.
     */
    private void open()
    {
        isOpen = true;
    }
    
    /**
     * This method closes the store. 
     */
    private void close()
    {
        isOpen = false;
    }
    
    /**
     * This method returns a string with information about 
     * the store's open status, i.e. open or closed.
     */
    private String getOpenStatus()
    {
        if ( isOpen )
        {
            openStatus = "The store is now open";
        }
        else
        {
            openStatus = "The store is now closed";
        }
        
        return openStatus;
    }
    
    /**
     * This method returns a string with information 
     * about the current time and day.
     */
    private String getCurrentTimeDay()
    {
        // if today is a closed day, it will append this text to the
        // returned string
        if ( day.getValue() == CLOSED_DAY )
        {
            appendClosedDay = " // closing day";
        }
        else
        {
            // sets the string to blank since today is not a closed day
            appendClosedDay = "";
        }
        
        return "The current time is: " + clock.getTime() + " "
                + day.getDisplayValue( day.getValue() ) + appendClosedDay;
    }
}
