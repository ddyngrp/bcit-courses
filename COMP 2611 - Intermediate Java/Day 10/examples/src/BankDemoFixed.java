public class BankDemoFixed {

	public static final int INITIAL_BALANCE = 10000;

	public static final int NACCOUNTS = 10;

	private int[] accounts;

	private int ntransacts;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		BankDemoFixed b = new BankDemoFixed();
		for (int i = 1; i <= BankDeadlock.NACCOUNTS; i++)
			new TransactionThread3(b, i).start();
	}

	public BankDemoFixed() {
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
		
		notifyAll();
	}

	public void test() {
		int sum = 0;
		for (int i = 0; i < NACCOUNTS; i++)
			sum += accounts[i];
		System.out.println("Transactions:" + ntransacts + " Sum: " + sum);
	}
}

class TransactionThread3 extends Thread {
	private BankDemoFixed bank;

	private int from;

	public TransactionThread3(BankDemoFixed b, int i) {
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
