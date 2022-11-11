// OS Lab 10
// Natthapong Lueangphumphitthaya 63011208

import java.util.concurrent.Semaphore;

public class BoundedBuffer
{
   private static final int   BUFFER_SIZE = 5;

   private int count; // number of items in the buffer
   private int in;   // points to the next free position in the buffer
   private int out;  // points to the next full position in the buffer
   private Object[] buffer;
   Semaphore mutex, full, empty;

   public BoundedBuffer()
   {
      // buffer is initially empty
      //A. Initialize count;  
      //B. Initialize in;
      //C. Initialize out;

      count = 0; //A; 
      in = 0; //B;
      out = 0; //C;
      buffer = new Object[BUFFER_SIZE];
      //D. create and initialize mutex semaphore 
      //E. create and initialize full semaphore
      //F. create and initialize empty semaphore

      mutex = new Semaphore(1);
      full = new Semaphore(0);
      empty = new Semaphore(BUFFER_SIZE);
      
   }

   //producer calls this method
   //G. Implement Insert method
    public void insert(Object item) throws InterruptedException{
        
        empty.acquire();
        mutex.acquire();

        ++count;
        buffer[in] = item;
        System.out.println("Producer Entered " + buffer[in] + " Buffer Size = " + count);
        in = (in + 1) % BUFFER_SIZE;

        mutex.release();
        full.release();
    }

   // consumer calls this method
   //H. Implement remove method  
    public Object remove() throws InterruptedException{
        
        full.acquire();
        mutex.acquire();

        --count;
        Object item = buffer[out];
        if(count == 0){
            System.out.println("Consumer Consumed " + buffer[out] + " Buffer EMPTY");
        }
        else{
            System.out.println("Consumer Consumed " + buffer[out] + " Buffer Size = " + count);
        }
        out = (out + 1) % BUFFER_SIZE;

        mutex.release();
        empty.release();
        return item;

    }
}