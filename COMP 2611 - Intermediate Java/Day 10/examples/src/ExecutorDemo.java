import java.util.concurrent.*;

public class ExecutorDemo {
  public static void main(String[] args) {
    // Create a fixed thread pool with maximum three threads
    ExecutorService executor = Executors.newFixedThreadPool(3);

    // Submit runnable tasks to the executor
    executor.execute(new TaskThreadDemo.PrintChar('a', 100));
    executor.execute(new TaskThreadDemo.PrintChar('b', 100));
    executor.execute(new TaskThreadDemo.PrintNum(100));

    // Shutdown the executor
    executor.shutdown();
  }
}
