// OS Lab 9
// Natthapong Lueangphumphitthaya 63011208

public class Main {
    public static void main (String[] args) throws InterruptedException {

        BoundedBuffer bb = new BoundedBuffer();

        Producer producerThread = new Producer(bb);
        Consumer consumerThread = new Consumer(bb);
        
        producerThread.start();
        consumerThread.start();
        producerThread.join();
        consumerThread.join();

        // System.out.println(counter.getCount());
    }
}

// javac Main.java
// java Main
