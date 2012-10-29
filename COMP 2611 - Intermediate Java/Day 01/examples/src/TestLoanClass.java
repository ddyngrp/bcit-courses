import javax.swing.JOptionPane;

public class TestLoanClass {
  /** Main method */
  public static void main(String[] args) {
    // Enter yearly interest rate
    String annualInterestRateString = JOptionPane.showInputDialog(
      "Enter yearly interest rate, for example 8.25:");

    // Convert string to double
    double annualInterestRate =
      Double.parseDouble(annualInterestRateString);

    // Enter number of years
    String numberOfYearsString = JOptionPane.showInputDialog(
      "Enter number of years as an integer, \nfor example 5:");

    // Convert string to int
    int numberOfYears = Integer.parseInt(numberOfYearsString);

    // Enter loan amount
    String loanString = JOptionPane.showInputDialog(
      "Enter loan amount, for example 120000.95:");

    // Convert string to double
    double loanAmount =  Double.parseDouble(loanString);

    // Create Loan object
    Loan loan =
      new Loan(annualInterestRate, numberOfYears, loanAmount);

    // Format to keep two digits after the decimal point
    double monthlyPayment =
      (int)(loan.getMonthlyPayment() * 100) / 100.0;
    double totalPayment =
      (int)(loan.getTotalPayment() * 100) / 100.0;

    // Display results
    String output = "The loan was created on " +
      loan.getLoanDate().toString() + "\nThe monthly payment is " +
      monthlyPayment + "\nThe total payment is " + totalPayment;
    JOptionPane.showMessageDialog(null, output);
  }
}
