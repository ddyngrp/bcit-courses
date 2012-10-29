package lego;

/**
 * This class is simply responsible for calculating the
 * factorial of a number.
 *   
 * @author Steffen L. Norgren, A00683006
 * @data 2008-10-12
 *
 */
public class Factorial {
	
	/**
	 * This recursive method returns a factorial of an input number.
	 * 
	 * @param n the number who's factorial we want to calculate
	 * @return Integer the resulting factorial
	 */	
	public int factorial(int n) {
        if(n <= 1) {
            return 1;
        }
        else {
            return n * factorial(n - 1);
        }
    }

	/**
	 * This recursive method returns a factorial of an input number.
	 * 
	 * @param n the number who's factorial we want to calculate
	 * @return long the resulting factorial
	 */	
	public long factorial(long n) {
        if(n <= 1) {
            return 1;
        }
        else {
            return n * factorial(n - 1);
        }
    }
}
