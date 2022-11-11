// OS Lab 9
// Natthapong Lueangphumphitthaya 63011208

public class Producer extends Thread {
    public BoundedBuffer obj; // counter
    public Producer(BoundedBuffer c) { // okay!
        obj = c;
    }
    @Override
    public void run(){ // 20 loops, call insert inside the loop
        try {
            for(int i = 0; i < 20; i++){
                obj.insert(i); // 1
            }
        } catch (InterruptedException ex) {
            
        }
    }
}
