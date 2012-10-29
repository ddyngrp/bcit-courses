import java.util.ArrayList;
import java.util.Iterator;

/**
 * Bank class holds any number of BankAccount objects.
 * COMP 1451 lab 3 -- there are a number of deliberate bugs in the project.
 * 
 * @author Colleen Penrowley 
 * @version July 2007
 */
public class Bank
{
    private ArrayList<BankAccount> accounts;

    /**
     * Constructor for objects of class Bank
     */
    public Bank()
    {
        accounts = new ArrayList<BankAccount>();
    }

    /**
     * Opens a new bank account, customer name and opening
     * balance to be specified.
     * 
     * @param  String customer name -- double opening balance
     */
    public void openAccount(String customerName, double openingBalance)
    {
        accounts.add(new BankAccount(customerName, openingBalance));
    }
    
     /**
     * Opens a new bank account, customer name to be specified.
     * 
     * @param  String name of customer
     */   
    public void openAccount(String customerName)
    {
        accounts.add(new BankAccount(customerName));
    }

     /**
     * Adds an existing account to the bank.
     * 
     * @param  BankAccount account to be added
     */
    public void openAccount(BankAccount account)
    {
        accounts.add(account);
    }
    
    
    /**
     * Gets the size of the bank
     * 
     * @return int number of accounts in the bank
     */
    public int numberOfAccounts()
    {
        return accounts.size();
    }
    
    
    /**
     * Applies interest to all accounts in the bank.
     */
    public void applyInterest()
    {
        for (BankAccount account : accounts){
            account.applyInterest();
        }
    }
    
    
    /**
     * Displays information about all the accounts in 
     * the bank.
     */
    public void showAccountInfo()
    {
        for (BankAccount account : accounts){
            System.out.println(account);
        }        
    }
    
    
    /**
     * Removes the account with the specified account number
     * Tests parameter to determine if valid
     * 
     * @param int unique account number of the account to remove
     */
    public void removeAccount(int accountToRemove)
    {
        if ((accountToRemove >= 0) && (accountToRemove < numberOfAccounts())) {
           accounts.remove(accountToRemove);
        }
    }
    
    
    /**
     * Returns a specified account
     * Tests parameter to determine if valid
     *
     * @param int unique account number of the account we want
     * 
     * @return BankAccount account with the specified account number or null if it does not exist
     */
    public BankAccount getAccount(int accountWanted)
    {
        if ((accountWanted >= 0) && (accountWanted < numberOfAccounts())) {
           return accounts.get(accountWanted);
        }
        return null;  // no such account
    }
}
