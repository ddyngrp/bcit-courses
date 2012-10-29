package editsteps;

import java.util.*;

/**
 * This class will parse data passed in from an array list.
 * It will then store our dictionaries and transformations in
 * a map to be retrieved for later processing.
 * 
 * @author Steffen L. Norgren, A00683006
 * @data 2008-11-23
 *
 */
public class ParseData {
	private static final String sCase = "// Test Case ";
	private static final int maxCases = 100;		// Max number of cases
	private static final int maxWords = 2000;		// Max number of words per case
	private static final int maxTransforms = 100;	// Max number of transforms per case

	// contains dictionary for each case
	private Map<Integer, ArrayList<String>> wordMap;
	// contains transformations for each case
	private Map<Integer, Map<String, String>> transformMap;
	
	/**
	 * Returns the wordMap for all our test cases.
	 * 
	 * @return Map<Integer, ArrayList<String>> wordMap
	 */
	public Map<Integer, ArrayList<String>> getWordMap() {
		return wordMap;
	}
	
	/**
	 * Returns the wordMap for all our test cases.
	 * 
	 * @return Map<Integer, Map<String, String>> transformMap
	 */
	public Map<Integer, Map<String, String>> getTransformMap() {
		return transformMap;
	}

	/**
	 * Parses data from an input file and add each dictionary
	 * word into a graph. Also adds each transformation we'll
	 * process into an ArrayList.
	 * 
	 * @param parseData ArrayList<String>, data to be parsed
	 */
	public ParseData(ArrayList<String> parseData) {
		int iCurrentCase = 0;
		int iLength = parseData.size();
		int testCases = 0;
		int transformCases = 0;
		
		// Initialize our maps
		wordMap = new HashMap<Integer, ArrayList<String>>(maxCases);
		transformMap = new HashMap<Integer, Map<String, String>>(maxCases);
		
		if (iLength < 4) {
			System.err.println("ERROR: Input file too short.");
		}
		
		try {
			// Test cases are limited to 1 < testCases <= 100
			testCases = Integer.parseInt(parseData.get(0).trim());
		}
		catch (NumberFormatException error) {
			System.err.println("java.lang.NumberFormatException: " + error.getMessage());
		}

		// Cycle through our input data
		for (int i = 1; i < iLength; ++i) {
			if (parseData.get(i).trim().toLowerCase().contains(sCase.toLowerCase().trim())) {
				iCurrentCase++;
				
				// Verify the number of cases in the file don't exceed the
				// stated number of cases.
				if (iCurrentCase > testCases) {
					System.err.println("ERROR: Test cases in file exceed " + "" +
							"number of stated test cases.");
					System.exit(1);
				}
				
				// Create the dictionary & transform list for the current case
				if (iCurrentCase != maxCases) {
					wordMap.put(iCurrentCase, new ArrayList<String>(maxWords));
					transformMap.put(iCurrentCase, 
							new HashMap<String, String>(maxTransforms));
				}
				else {
					System.err.println("ERROR: Exceeded " + maxCases + " cases.");
					System.exit(1);
				}
				++i; // skip over the current line
			}
			
			// Parse the transformation declaration
			if (parseData.get(i).trim().contains("* ")) {
				StringTokenizer st = new StringTokenizer(parseData.get(i));
				
				// Verify correctness of the declaration format
				if (st.countTokens() > 2) {
					System.err.println("Invalid transformation declaration.");
					System.exit(1);
				}
				else if (st.nextToken().equals("*")) {
					try {
						// Transformation cases are limited to 1 < transformCases <= 100
						transformCases = Integer.parseInt(st.nextToken());
						
						// Cycle through our transformation cases
						for (int k = 0; k < transformCases; ++k) {
							st = new StringTokenizer(parseData.get(++i));
							
							// Verify we're only dealing with 2 words
							if (st.countTokens() != 2) {
								System.err.println("ERROR: Invalid amount of transformation "
										+ "words.");
								System.exit(1);
							}
							else {
								String transFrom = st.nextToken();
								String transTo = st.nextToken();
								
								// Add our transformation to the map
								if (transformMap.get(iCurrentCase).size() != maxTransforms) {
									transformMap.get(iCurrentCase).put(transFrom, transTo);
								}
								else {
									System.err.println("ERROR: Exceeded " + maxTransforms +
											" transformations for the current test case.");
									System.exit(1);
								}
							}
						}
						continue; // continue to the next line
					}
					catch (NumberFormatException error) {
						System.err.println("java.lang.NumberFormatException: "
								+ error.getMessage());
					}
				}
			}

			// Add word to the map (limit of 1 < words <= 2000)
			if (wordMap.get(iCurrentCase).size() != maxWords) {
				wordMap.get(iCurrentCase).add(parseData.get(i).trim());
			}
			else {
				System.err.println("ERROR: Exceeded " + maxWords + " words for the " +
						"current test case.");
				System.exit(1);
			}
		}
	}
	
	@Override public String toString() {
		String returnString = "";
		Iterator<Map.Entry<Integer, ArrayList<String>>> wmIT = 
			wordMap.entrySet().iterator();
		Iterator<Map.Entry<Integer, Map<String, String>>> tmIT = 
			transformMap.entrySet().iterator();
		
		while (wmIT.hasNext() && tmIT.hasNext()) {
			
			Map.Entry<Integer, ArrayList<String>> words = wmIT.next();
			int currentCase = words.getKey();
			
			returnString += "// Test Case " + currentCase + "\n";
			
			for (String s : words.getValue()) {
				returnString += s + "\n";
			}
			
			Map<String, String> transforms = tmIT.next().getValue();
			for (String s : transforms.keySet()) {
				returnString += s + "->" + transforms.get(s) + "\n";
			}
		}
		
		return returnString;
	}
}
