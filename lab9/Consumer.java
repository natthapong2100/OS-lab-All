// OS Lab 9
// Natthapong Lueangphumphitthaya 63011208

public class Consumer extends Thread {
    public BoundedBuffer obj;
    public Consumer(BoundedBuffer c) {
        obj = c;
    }
    @Override
    public void run() { // can throw interupt exception
        try {
            for(int i = 0; i < 20; i++){
                obj.remove();
            }
        } catch (InterruptedException ex) {
            
        }
    }
}
