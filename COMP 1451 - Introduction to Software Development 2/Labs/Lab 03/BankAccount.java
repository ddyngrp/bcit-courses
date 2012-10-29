
/**
 * BankAccount class models a simple bank account. Each account
 * has a unique account number, as well as a customer name and current balance.
 * COMP 1451 lab 3 -- there are a number of deliberate bugs in the project.
 * 
 * @author Colleen Penrowley 
 * @version July 2007
 */
public class BankAccount
{

    /** percentage to be added to balance each time applied */
//    public static double INTEREST_RATE = 1.0; // currently one percent
    public static double INTEREST_RATE = 0.01; // currently one percent

    private double currentBalance;          // current balance in the account
    private static int objectNumber;        // current object number deliciousness
    private int accountNumber;              // unique account number
    private String customerName;            // customer whose account this is


    /**
     * Constructor for objects of class BankAccount
     */
    public BankAccount(String customerName)
    {
        this.customerName = customerName;
        currentBalance = 0.0;
        objectNumber++;                     // get the next available number
        accountNumber = objectNumber;       // get the next available number
    }
    
    /**
     * Constructor for objects of class BankAccount
     */
    public BankAccount(String customerName, double initialBalance)
    {
        this.customerName = customerName;
        if (initialBalance > 0) {
            currentBalance = initialBalance;
        }
        else {
            currentBalance = 0.0;
        }
        objectNumber++;                     // get the next available number
        accountNumber = objectNumber;       // get the next available number
    }

    /**
     * Gets the balance in the account
     * 
     * @return  double current balance in the account
     */
    public double getBalance()
    {
        return currentBalance;
    }
    
    /**
     * Deposits the specified amount to the account. 
     * Tests the parameter for validity
     * 
     * @param double amount to be deposited to the account
     */
    public void deposit(double amountToDeposit)
    {
        if (amountToDeposit > 0) {
            currentBalance += amountToDeposit;
        }
    }
 
    /**
     * Withdraws the specified amount from the account.
     * Tests the parameter for validity
     * 
     * @param double amount to withdraw from the account
     */
    public void withdraw(double amountToWithdraw) 
    {
        if (amountToWithdraw <= currentBalance) {
           currentBalance -= amountToWithdraw;   
        }
    }

    /**
     * Returns the unique identifier for this account
     * 
     * @return int unique identifier for this account
     */
    public int getAccountNumber()
    {
        return accountNumber;
    }

    /**
     * Returns the customer name
     * 
     * @return String customer name of this account
     */
    public String getCustomerName()
    {
        return customerName;
    }

    
    /**
     * Adds interest to the account balance, based on current 
     * interest rate. Each time the method is invoked, the percentage
     * is calculated and added to the account balance.
     */
    public void applyInterest()
    {
        //currentBalance =+ (currentBalance * INTEREST_RATE);
        currentBalance += (currentBalance * INTEREST_RATE);
    }

    
    /**
     * Provides account info.
     * 
     * @return account details: customer name, account number, current balance
     */
    public String toString()
    {
        return "Name: " + customerName + " Account #: " + accountNumber + " Balance: " + currentBalance;
    }
    
}
