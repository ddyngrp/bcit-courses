package editsteps;

import java.util.*;

/**
 * This class creates an adjacency list based on a set
 * of dictionary words. Each node in the list differs from
 * its adjacent node by only one character. It also contains
 * functions to calculate traversals from one node to another.
 * 
 * @author Steffen L. Norgren, A00683006
 * @data 2008-11-22
 *
 */
public class AdjacencyList {
	private Map<String, ArrayList<String>> adjList;

	/**
	 * Create our initial adjacency list.
	 * @param words
	 */
	public AdjacencyList(ArrayList<String> words) {
		adjList = new HashMap<String, ArrayList<String>>(words.size());
		
		// Add the list of words as our keys and create a new ArrayList
		// for each entry to hold the adjacent nodes
		for (String s : words) {
			adjList.put(s.toLowerCase(), new ArrayList<String>());
		}
		CalculateAdjacentNodes();
	}
	
	/**
	 * Calculate the adjacency nodes for each entry
	 */
	private void CalculateAdjacentNodes() {
		Iterator<String> adjKeyIT = adjList.keySet().iterator();
		
		while (adjKeyIT.hasNext()) {
			String compare = adjKeyIT.next();
			
			Iterator<Map.Entry<String, ArrayList<String>>> adjIT = adjList.entrySet().iterator();
			while (adjIT.hasNext()) {
				Map.Entry<String, ArrayList<String>> node = adjIT.next();
				String key = node.getKey();
				
				if (WordDifference(key, compare) == 1) {
					adjList.get(key).add(compare);
				}
			}
		}
	}
	
	/**
	 * Returns the number of character differences
	 * between two words.
	 * @param a first word
	 * @param b second word
	 * @return number of differences
	 */
	private int WordDifference(String a, String b) {
		int diffCount = 0;

		if (a.length() - b.length() == 1 && a.contains(b)) {
			return 1;
		}
		else if (b.length() - a.length() == 1 && b.contains(a)) {
			return 1;
		}
		else if (a.length() - b.length() == 0) {
			for (int i = 0; i < a.length(); ++i) {
				if(a.charAt(i) != b.charAt(i)) {
					++diffCount;
				}
			}
		}
		else if (a.length() > b.length()) {
			for (int i = 0; i < b.length(); ++i) {
				if(a.charAt(i) != b.charAt(i)) {
					++diffCount;
				}
				diffCount += a.length() - b.length();
			}			
		}
		else if (b.length() > a.length()) {
			for (int i = 0; i < a.length(); ++i) {
				if(a.charAt(i) != b.charAt(i)) {
					++diffCount;
				}
				diffCount += b.length() - a.length();
			}			
		}
		
		return diffCount;
	}
	
	/**
	 * Finds the shortest traversal given a starting and ending word.
	 * @param start word to start from
	 * @param end word to end with
	 * @return number of transformations needed.
	 */
	public int ShortestTraversal(String start, String end) {
		String current = start;
		int wordDiff = Integer.MAX_VALUE;
		int minIndex = 0;
		int stepCount = 0;

		// Check to see if the node has any adjacent nodes
		if (adjList.get(start).size() == 0) {
			return -1;
		}
		
		if (start.equalsIgnoreCase(end)) {
			return 0;
		}
		
		// Continue transforming until we reach the end word
		while (!current.equalsIgnoreCase(end)) {
			for (int i = 0; i < adjList.get(current).size(); ++i) {
				if (WordDifference(adjList.get(current).get(i), end) < wordDiff) {
					wordDiff = WordDifference(adjList.get(current).get(i), end);
					minIndex = i;
				}
			}
			wordDiff = Integer.MAX_VALUE;
			String previous = current;
			current = adjList.get(current).get(minIndex);
			adjList.get(current).remove(previous);
			stepCount++;
		}
		
		return stepCount;
	}
	
	/** 
	 * Don't ask!
	 * @return
	 */
	public int Ladder() {
		int first = 0;
		int second = 0;
		
		Iterator<Map.Entry<String, ArrayList<String>>> adjIT = adjList.entrySet().iterator();
		while (adjIT.hasNext()) {
			int size = adjIT.next().getValue().size();
			
			if (size > first) {
				second = first;
				first = size;
			}
		}
		
		return (first + second);
	}
	
	@Override public String toString() {
		Iterator<Map.Entry<String, ArrayList<String>>> adjIT = adjList.entrySet().iterator();
		
		while (adjIT.hasNext()) {
			System.out.println(adjIT.next().toString());
		}
		
		return "this";
	}
}
