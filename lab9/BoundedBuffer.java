// OS Lab 9
// Natthapong Lueangphumphitthaya 63011208

import java.util.Random;

public class BoundedBuffer
{
   private static final int BUFFER_SIZE = 5;
   private int count; // number of items in the buffer
   private int in;   // points to the next free position in the buffer
   private int out;  // points to the next full position in the buffer
   private Object[] buffer;

   public BoundedBuffer()
   {
      // buffer is initially empty
      count = 0; //A; 
      in = 0; //B;
      out = 0; //C;
      buffer = new Object[BUFFER_SIZE];
   }

   //producer calls this method
   //implements insert method
    public synchronized void insert(Object item)throws InterruptedException {

        while(count == BUFFER_SIZE){
            wait();
        }
        ++count;
        buffer[in] = item;
        System.out.println("Producer Entered " + buffer[in] + " Buffer Size = " + count);
        in = (in + 1) % BUFFER_SIZE;
        notify();
        
    }
   // consumer calls this method
   //implements remove method

    public synchronized Object remove() throws InterruptedException{

        while(count == 0){
            wait();
        }
        --count;
        Object item = buffer[out];
        if(count == 0){
            System.out.println("Consumer Consumed " + buffer[out] + " Buffer EMPTY");
        }
        else{
            System.out.println("Consumer Consumed " + buffer[out] + " Buffer Size = " + count);
        }
        out = (out + 1) % BUFFER_SIZE;
        notify();
        return item;
    }
}