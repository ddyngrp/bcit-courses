class BankDemoDeadlock {
	public static void main(String[] args) {
		BankDeadlock b = new BankDeadlock();
		for (int i = 1; i <= BankDeadlock.NACCOUNTS; i++)
			new TransactionThread2(b, i).start();
	}
}

class BankDeadlock {
	public static final int INITIAL_BALANCE = 10000;

	public static final int NACCOUNTS = 10;

	private int[] accounts;

	private int ntransacts;

	public BankDeadlock() {
		accounts = new int[NACCOUNTS];
		for (int i = 0; i < NACCOUNTS; i++)
			accounts[i] = INITIAL_BALANCE;
		ntransacts = 0;
		test();
	}

	public synchronized void transfer(int from, int to, double amount) {
		while (accounts[from] < amount) {
			try {
				wait();
			} catch (InterruptedException e) {
			}
		}
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
		if (ntransacts % 500 == 0) {
			test();
		}
	}

	public void test() {
		int sum = 0;
		for (int i = 0; i < NACCOUNTS; i++)
			sum += accounts[i];
		System.out.println("Transactions:" + ntransacts + " Sum: " + sum);
	}
}

class TransactionThread2 extends Thread {
	private BankDeadlock bank;

	private int from;

	public TransactionThread2(BankDeadlock b, int i) {
		from = i - 1;
		bank = b;
	}

	public void run() {
		while (true) {
			int to = (int) ((BankDeadlock.NACCOUNTS - 1) * Math.random());
			if (to == from)
				to = (to + 1) % BankDeadlock.NACCOUNTS;

			int amount = (int) (BankDeadlock.INITIAL_BALANCE * Math.random());
			bank.transfer(from, to, amount);
			try {
				sleep(1);
			} catch (InterruptedException e) {
			}
		}
	}
}
