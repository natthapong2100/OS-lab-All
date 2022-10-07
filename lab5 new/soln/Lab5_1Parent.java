import java.util.Scanner;
import Lab5_1Child;

public class Lab5_1Parent {

    public static void main(String[] args) {
        Scanner inp = new Scanner(System.in);
        int num = 0, sum = 0;
        System.out.print("Please enter number ");
        num = inp.nextInt();
        inp.nextLine();

        Lab5_1Child child = new Lab5_1Child(num);
        child.start();
        
        for(int i =1; i <= num; i++) {
            sum += i;
        }
        try {
            child.join();
        } catch (InterruptedException ex) {
            
        }
        System.out.println("I am parent my sum is " + sum);
        System.out.println("The final result is " + (sum + child.getSum()));

    }
    
}