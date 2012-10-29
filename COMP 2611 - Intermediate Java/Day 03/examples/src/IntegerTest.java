class IntegerTest {
	public static void main(String[] args) {
		Integer integer1 = new Integer("120");
		Integer integer2 = new Integer(120);

		try {
			Integer.parseInt("2102");
		} catch (NumberFormatException nfe) {
			System.out.println("Not a valid integer");
		}

		System.out.println("integer1 " + integer1.intValue());
		System.out.println("integer2 " + integer2.intValue());
	}
}
