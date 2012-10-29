/**
 * Project: final_b1
 * File: B1.java
 * Date: 30-Nov-07
 * Time: 8:00:00 PM
 */
package a00683006;

import java.io.*;
import java.util.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class B1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new B1();
	}
	
	private B1() {
		String firstName;
		String middleName;
		String lastName;
		String preferredName;
		int votes;
		ReadFile readFile = new ReadFile();
		ArrayList<MyCandidate> candidates = new ArrayList<MyCandidate>();
		
		for(String line : readFile.textFile("B1_in.txt")) {
			StringTokenizer st=new StringTokenizer(line, "\t");
			
			while (st.hasMoreTokens()) {
				firstName = st.nextToken();
				middleName = st.nextToken();
				lastName = st.nextToken();
				preferredName = st.nextToken();
				votes = Integer.parseInt(st.nextToken());
				
				if (!preferredName.equals(" ")) {
					firstName = preferredName;
				}
				candidates.add(new MyCandidate(firstName, lastName, votes));
			}
		}
		
		int fNameLength = 0;
		int lNameLength = 0;
		int votesMax = 0;
		for (MyCandidate n : candidates) {
			if (n.firstName.length() > fNameLength) {
				fNameLength = n.firstName.length();
			}
			if (n.lastName.length() > lNameLength) {
				lNameLength = n.lastName.length();
			}
			if (n.votes > votesMax) {
				votesMax = n.votes;
			}			
		}
		
		
		File file = new File("B1_out.txt");

		// Create a file
		try {
			PrintWriter output = new PrintWriter(file);
			
			String outString = "";
			for (MyCandidate out : candidates) {
				outString += returnSpace(fNameLength - out.firstName.length());
				outString += out.firstName;
				outString += " " + returnSpace(lNameLength - out.lastName.length());
				outString += out.lastName;
				if (out.votes >= 100) {
					outString += "  ";
				}
				else {
					outString += "   ";
				}
				outString += out.votes;
				output.println(outString);
				outString = "";
			}

			output.close();
		}
		catch (FileNotFoundException ex) {
			// do nothing
		}
	}
	
	private String returnSpace(int n) {
		String returnString = "";
		for (int i = 0; i < n; i++) {
			returnString += " ";
		}
		return returnString;
	}
	
	private class MyCandidate {
		private String firstName;
		private String lastName;
		private int votes;
		
		public MyCandidate(String firstName, String lastName, int votes) {
			this.firstName = firstName;
			this.lastName = lastName;
			this.votes  = votes;
		}
	}
}
