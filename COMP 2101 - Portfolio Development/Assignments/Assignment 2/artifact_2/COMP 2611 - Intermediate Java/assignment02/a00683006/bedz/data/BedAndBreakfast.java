/**
 * Project: assignment02
 * File: BedAndBreakfast.java
 * Date: 1-Oct-07
 * Time: 7:38:59 PM
 */
package a00683006.bedz.data;

import java.util.*;
import java.io.*;
import a00683006.bedz.util.*;

/**
 * Holds data on BedAndBreakfast objects. This class loads data from
 * individual text files and stores the data from those text files into
 * Collections.
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class BedAndBreakfast {
	
	private ArrayList<Room> room;
	private HashMap<String, Guest> guests;
	private HashMap<Integer, Reservation> reservations;
	private String bedAndBreakfast;
	
	/**
	 * Creates a new BedAndBreakfast object with a particular name to
	 * identify the B&B. It then loads the data from all relevant files
	 * and loads it into HashMaps.
	 * @param bedAndBreakfast
	 */
	public BedAndBreakfast(String bedAndBreakfast) {
		this.bedAndBreakfast = bedAndBreakfast;
		
		// Initialize the HashMaps
		room = new ArrayList<Room>();
		guests = new HashMap<String, Guest>();
		reservations = new HashMap<Integer, Reservation>();
		
		// Read the Rooms.txt file and populate the room HashMap
		for (String currentRoom : new ReadFile().textFile("Rooms.txt")) {
			StringTokenizer st=new StringTokenizer(currentRoom, "\t");
			int number = Integer.parseInt(st.nextToken());
			float rate = Float.parseFloat(st.nextToken());
			String name = st.nextToken();
			String description = st.nextToken();
			String imageName = st.nextToken();
			int maximumNumberOfGuests = Integer.parseInt(st.nextToken());
			room.add(new Room(number, rate, name, description,
					imageName, maximumNumberOfGuests));
		}		

		if (new File("Guests.xml").exists()) {
			try {
				setGuests(ReadWriteXML.importXML("Guests.xml"));
			}
			catch (IOException ex) {
				// we don't care
			}
		}
		else {
			// Read the Guests.txt file and populate the room HashMap
			for (String currentGuest : new ReadFile().textFile("Guests.txt")) {
				StringTokenizer st=new StringTokenizer(currentGuest, "\t");
				Integer id = Integer.parseInt(st.nextToken());
				String lastName = st.nextToken();
				String firstName = st.nextToken();
				String phoneNumber = st.nextToken();
				String emailAddress = st.nextToken();
				String street = st.nextToken();
				String city = st.nextToken();
				String province = st.nextToken();
				String postalCode = st.nextToken();
				String country = st.nextToken();
				
				try {
					guests.put(lastName + ", " + firstName,
							new Guest(id, lastName, firstName, phoneNumber, emailAddress,
							new Address(street, city, Province.getProvince(province),
									postalCode, country)));
				}
				catch (DataException ex) {
					System.out.println(ex);
				}
			}			
		}

		// Read the Reservations.txt file and populate the room HashMap
		for (String currentReservation : new ReadFile().textFile("Reservations.txt")) {
			StringTokenizer st=new StringTokenizer(currentReservation, "\t");
			Integer id = Integer.parseInt(st.nextToken());
			Integer roomNumber = Integer.parseInt(st.nextToken());
			Integer guestId = Integer.parseInt(st.nextToken());
			Payment payment = new Payment(Float.parseFloat(st.nextToken()));
			reservations.put(id, new Reservation(id, roomNumber, guestId, payment));
		}		
	}
	
	/**
	 * Creates a BedAndBreakfast object using the following parameters.
	 * @param room
	 * @param guests
	 * @param reservations
	 */
	public BedAndBreakfast(ArrayList<Room> room,
			HashMap<String, Guest> guests,
			HashMap<Integer, Reservation> reservations) {
		setRoom(room);
		setGuests(guests);
		setReservations(reservations);
	}

	/**
	 * @return the room
	 */
	public ArrayList<Room> getRoom() {
		return room;
	}

	/**
	 * @param room the room to set
	 */
	public void setRoom(ArrayList<Room> room) {
		this.room = room;
	}

	/**
	 * @return the guests
	 */
	public HashMap<String, Guest> getGuests() {
		return guests;
	}

	/**
	 * @param guests the guests to set
	 */
	public void setGuests(HashMap<String, Guest> guests) {
		this.guests = guests;
	}

	/**
	 * @return the reservations
	 */
	public HashMap<Integer, Reservation> getReservations() {
		return reservations;
	}

	/**
	 * @param reservations the reservations to set
	 */
	public void setReservations(HashMap<Integer, Reservation> reservations) {
		this.reservations = reservations;
	}

	/**
	 * @return the bedAndBreakfast
	 */
	public String getBedAndBreakfast() {
		return bedAndBreakfast;
	}

	/**
	 * @param bedAndBreakfast the bedAndBreakfast to set
	 */
	public void setBedAndBreakfast(String bedAndBreakfast) {
		this.bedAndBreakfast = bedAndBreakfast;
	}
}