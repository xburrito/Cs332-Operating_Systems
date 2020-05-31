// Libraries used
import java.util.Scanner;

public class Main {

  // Upper bound range between 0 - 10,000
  private final static int maxVal = 10000;
  private static int maxDivCount = 0;
  private static int maxDivCountHolder;

  /* Method called by thread after completing computation
     Returns largest num of divisors found in range of ints */
  synchronized private static void report(int maxCountFromThread, int intWithMaxFromThread) {
    if (maxCountFromThread > maxDivCount) {
      maxDivCount = maxCountFromThread;
      maxDivCountHolder = intWithMaxFromThread;
    }
  }

  /* Threads from this class counts num of divisors for all ints within range
     Range specified in constructor
     Report() called to return largest num of divisors */
  private static class CountDivisorsThread extends Thread {
    int min, max;

    public CountDivisorsThread(int min, int max){
      this.min = min;
      this.max = max;
    }

    public void run() {
      int maxDiv = 0;
      int intVal = 0;
      for (int i = min; i < max; i++) {
        int divs = countDivs(i);
        if (divs > maxDiv) {
          maxDiv = divs;
          intVal = i;
        }
      }

      report(maxDiv,intVal);
    }
  }

  /* Finds the number in the range 1 to 10000 that has the largest num
     Divides the task among the number of threads */
  private static void countDivThreads(int numThreads) {
    System.out.println("\nCounting divisors using " + numThreads + " thread(s)...");
    long startTime = System.currentTimeMillis();
    CountDivisorsThread[] threads = new CountDivisorsThread[numThreads];
    int intsPerThread = maxVal / numThreads;
    int start = 1;  // Starting point of the range of ints for first thread
    int end = start + intsPerThread - 1;  // Endpoint of the range
    for (int i = 0; i < numThreads; i++) {
      if (i == numThreads - 1) {
        end = maxVal;  /* Make sure that the last thread's range goes all
                          the way up to maxVal value */
    }

    threads[i] = new CountDivisorsThread(start, end);
    start = end+1;  // Determine the range of ints for the NEXT thread
    end = start + intsPerThread - 1;
  }

    maxDivCount = 0;
    for (int i = 0; i < numThreads; i++){
      threads[i].start();
    }
    for (int i = 0; i < numThreads; i++){
      /* Wait for each thread to die, because the results
         require each task to complete and terminate before
         reporting back their results */
      while (threads[i].isAlive()) {
        try {
          threads[i].join();
        }
        catch (InterruptedException e) {
          }
      }
    }

    long elapsedTime = System.currentTimeMillis() - startTime;
    System.out.println("\nThe largest number of divisors for numbers between 1 and " + maxVal + " is " + maxDivCount);
    System.out.println("An integer with that many divisors is " + maxDivCountHolder);
    System.out.println("Total elapsed time: " + (elapsedTime / 1000.0) + " seconds.\n");
  }

  /* Gets the number of threads from the user and calls
     CountDivisorsWithThreads() to start the process */
  public static void main(String[] args) {
    Scanner keyboard = new Scanner(System.in);
    int numThreads = 0;
    while (numThreads < 1 || numThreads > 10) {
      System.out.print("Number of threads that will be used between 1 - 10: ");
      numThreads = keyboard.nextInt();
      if (numThreads < 1 || numThreads > 10)
        System.out.println("Only integers ranging from 1 - 10 are accepted!");
    }

    countDivThreads(numThreads);
  }

  // Finds num of divisors between 1 - N that divides evenly with N
  public static int countDivs(int N) {
    int count = 0;
    for (int i = 1; i <= N ; i++) {
      if ( N % i == 0 )
        count ++;
    }

    return count;
  }
}
