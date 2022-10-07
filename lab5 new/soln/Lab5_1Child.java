
public class Lab5_1Child extends Thread {
    private int num;
    private int sum = 0;
    public Lab5_1Child(int num) {
        this.num = num;
    }
    public int getSum() {
        return sum;
    }
    public void run() {
        
        for(int i =1; i <= 2 * num; i++ ) {
            sum += i;
        }
        System.out.println("I am child my sum is " + sum);
    }
    
}