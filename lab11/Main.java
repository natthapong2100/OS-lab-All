// OS Lab 11
// Natthapong Lueangphumphitthaya 63011208

public class Main {
    public static void main(String[] args) throws InterruptedException, NullPointerException{
        int[][] array1 = {{5, 6, 7}, {4, 8, 9}};
        int[][] array2 = {{6, 4}, {5, 7}, {1, 1}};
        int rowResult = array1.length; // 2 X
        int colResult = array2[0].length; // X 2
        int[][] result = new int[rowResult][colResult];  
        //1 Define a 2D array of Multiplier where each element will be used to find the summation 
        //of each specified row multiply by each specified column     
        
        //2 create an object of each Multiplier element and start the thread of each element.
        // I declare and initialize multiplierThread
        // each element I initialize by using Constructor because without this step, it'll get error
        Multiplier[][] multiplierThread = {{new Multiplier(), new Multiplier()}, {new Multiplier(), new Multiplier()}};
        for(int i =0; i < rowResult; i++) { // 2
            for(int j =0; j < colResult; j++) { // 2
                multiplierThread[i][j] = new Multiplier(array1, array2, i, j); // i, j = pos in result matrix
                multiplierThread[i][j].start();
            }
        }
        
        //3 The Main program waits for all threads to complete their task.
        for(int i =0; i < rowResult; i++) {
            for(int j =0; j < colResult; j++) {
               multiplierThread[i][j].join();
            }
        }
        //4. Store the result of each thread into the result array.
        for(int i =0; i < rowResult; i++) {
            for(int j =0; j < colResult; j++) {
                result[i][j] = multiplierThread[i][j].getResult();
            }
        }
        
        //print result
        System.out.println("First Matrix");
        displayMatrix(array1);
        System.out.println("Second Matrix");
        displayMatrix(array2);
        System.out.println("Result Matrix");
        displayMatrix(result);
   }
    public static void displayMatrix(int [][] matrix) {
        for(int i = 0; i < matrix.length; i++) {
        for(int j = 0; j < matrix[0].length; j++) {
            System.out.print(matrix[i][j] + " ");
        }
        System.out.println();
        } 
    }

}
