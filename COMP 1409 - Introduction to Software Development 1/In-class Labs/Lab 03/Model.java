
/**
 * A class that models the attributes and behaviours of their models.
 * 
 * @author Steffen L. Norgren
 * @version May 1, 2007
 */
public class Model
{
    public static final int IN_PER_FOOT = 12; // how many inches there are in a foot
    public static final int BASE_RATE = 60; // base rate
    public static final int TALL_INCHES = 67; // model is tall at or above this many inches
    public static final double THIN_POUNDS = 140.0; // model is thin at or below this weight
    public static final int TALL_THIN_BONUS = 5; // bonux if model is tall and thin
    public static final int TRAVEL_BONUS = 4; // bonus if the model can travel
    public static final int SMOKER_DEDUCTION = 10; // deduction if model smokes

    String firstName; // model's first name
    String lastName; // model's last name
    int heightInInches; // model's height in inches
    double weightInPounds; // model's weight in pounds
    boolean canTravel; // model can travel
    boolean smokesButIsNotOnFire; // model smokes but is not currenly on fire
    
    /**
     * Constructor for objects of class Model
     */
    public Model( String modelFirstName, String modelLastName, int modelHeightInInches, 
                  double modelWeightInPounds, boolean modelCanTravel, 
                  boolean modelSmokesButIsNotOnFire )
    {
        firstName = modelFirstName;
        lastName = modelLastName;
        heightInInches = modelHeightInInches;
        weightInPounds = modelWeightInPounds;
        canTravel = modelCanTravel;
        smokesButIsNotOnFire = modelSmokesButIsNotOnFire;
    }

    /**
     * Converts the model's hight to feet and inches in the format of "5 feet 8 inches"
     */
    public String convertHeightToFeetInches()
    {
        // we can use an int in this conversion since we don't need the decimal result
        // if we have a remainder, we'll use modulus to give us the result
        return ( heightInInches / IN_PER_FOOT ) + " feet " + ( heightInInches % IN_PER_FOOT ) + " inches";
    }
    
    /**
     * Calculates the model's pay per hour
     */
    public int calculatePayPerHour()
    {
        // Sets the model's initial hourly wage to the base rate
        int hourlyWage = BASE_RATE;
        
        // Determines if the model qualifies for the tall and thin bonus
        if ( weightInPounds <= THIN_POUNDS && heightInInches >= TALL_INCHES )
        {
            hourlyWage += TALL_THIN_BONUS;
        }
        
        // Determines if the model qualifies for the travel bonux
        if ( canTravel == true )
        {
            hourlyWage += TRAVEL_BONUS;
        }
        
        // Determines if the model qualifies for the smoking, but not being on fire deduction
        if ( smokesButIsNotOnFire == true )
        {
            hourlyWage -= SMOKER_DEDUCTION;
        }
        
        return hourlyWage;
    }

    /**
     * Display's all the model's information on the screen.
     */
    public void displayModelDetails()
    {
        // initialize variables to be filled with yes/no values
        String canTravelYesNo;
        String smokesButIsNotOnFireYesNo;
        
        // Convert boolean values into yes/no answer
        if ( canTravel == true )
            canTravelYesNo = "yes";
        else
            canTravelYesNo = "no";
            
        // Convert boolean values into yes/no answer
        if ( smokesButIsNotOnFire == true )
            smokesButIsNotOnFireYesNo = "yes";
        else
            smokesButIsNotOnFireYesNo = "no";
        
        System.out.println("Name: " + firstName + " " + lastName );
        System.out.println("Height: " + convertHeightToFeetInches() );
        System.out.println("Weight: " + (int)weightInPounds + " pounds" );
        System.out.println("Travels: " + canTravelYesNo + " Smokes: " + smokesButIsNotOnFireYesNo );
        System.out.println("Hourly rate: $" + calculatePayPerHour() );
    }
}
