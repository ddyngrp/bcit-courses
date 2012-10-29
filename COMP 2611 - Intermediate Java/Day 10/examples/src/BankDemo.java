class BankDemo {
	public static void main(String[] args) {
		Bank b = new Bank();
		for (int i = 1; i <= Bank.NACCOUNTS; i++)
			new TransactionThread1(b, i).start();
	}
}// end clas BankDemo

class Bank {
	public static final int INITIAL_BALANCE = 10000;

	public static final int NACCOUNTS = 10;

	private int[] accounts;

	private int ntransacts;

	public Bank() {
		accounts = new int[NACCOUNTS];
		for (int i = 0; i < NACCOUNTS; i++)
			accounts[i] = INITIAL_BALANCE;
		ntransacts = 0;
		test();
	}

	public void transfer(int from, int to, double amount) {
		accounts[from] -= amount;
		// simulates transaction delay ...
		try {
			Thread.sleep(1);
		} catch (InterruptedException e) {
		}
		accounts[to] += amount;
		// simulates transaction delay ...
		try {
			Thread.sleep(1);
		} catch (InterruptedException e) {
		}
		ntransacts++;

		if (ntransacts % 500 == 0)
			test();
	}

	public void test() {
		int sum = 0;
		for (int i = 0; i < NACCOUNTS; i++)
			sum += accounts[i];
		System.out.println("Transactions:" + ntransacts + " Sum: " + sum);
	}
}// end class Bank

class TransactionThread1 extends Thread {
	private Bank bank;

	private int from;

	public TransactionThread1(Bank b, int i) {
		from = i - 1;
		bank = b;
	}

	public void run() {
		while (true) {
			int to = (int) ((Bank.NACCOUNTS - 1) * Math.random());
			if (to == from)
				to = (to + 1) % Bank.NACCOUNTS;
			int amount = (int) (Bank.INITIAL_BALANCE * Math.random());
			bank.transfer(from, to, amount);
			try {
				sleep(1);
			} catch (InterruptedException e) {
			}
		}
	}
}