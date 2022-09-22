
// OS Lab 5 Q1
// Natthapong Lueangphumphitthaya 63011208

public class Foo extends Thread{
    private int data, result = 0;

    public int getResult(){
        return result;
    }
    
    public void setData(int data){
        this.data = data;
    }

    public void run() {
        for(int i = 1; i <= (data * 2); i++){
            result += i;
        }
        System.out.println("Child Thread");
    }

   public static void main(String args[]) {
        Foo runner = new Foo();

        int num = Integer.parseInt(args[0]);

        runner.setData(num);
        runner.start();

        try{
            runner.join();
        } catch(InterruptedException e){
            System.out.println("Interrupted Exception");
        }

        int parentNum = 0;
        for(int i = 1; i <= num; i++){
            parentNum += i;
        }
        System.out.println("Parent Thread"); // child, then parent
        System.out.println("The final result: " + (parentNum + runner.getResult()));
   }
}

// git remote add origin https://github.com/natthapong2100/OS-lab-All.git
// git branch -M main
// git push -u origin main



