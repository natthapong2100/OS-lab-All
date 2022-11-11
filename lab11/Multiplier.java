// OS Lab 11
// Natthapong Lueangphumphitthaya 63011208

public class Multiplier extends Thread {
    private int[][]a;
    private int[][]b;
    private int row, col;
    private int result;

    public Multiplier(){

    }
    public Multiplier(int[][] a, int[][]b, int row, int col) {
        this.result = 0;
        this.a = a;
        this.b = b;
        this.row = row;
        this.col = col;
    }
    @Override
    public void run() {
        //find the summation of the specified row in "a" multiplied by the specified col in "b".
        try{
            for(int i = 0; i < b.length; i++){ // b.length = 3
                result += a[row][i] * b[i][col];
            }
        }
        catch(NullPointerException n){

        }
        
        
        
    }
    public int getResult() {
        return result;
    }
}