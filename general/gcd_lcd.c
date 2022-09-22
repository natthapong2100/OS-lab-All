#include <stdio.h>

int main(){

    int x, y, i;
    int amount = 0; // like size but can change the value
    int b[100]; 

    printf("------ GCD LCD Problem ------\n");
    printf("| let x = a * b and y = b * c |\n");
    printf(" show all possibility a, b, c |\n");
    printf("-------------------------------\n");

    printf("Enter x , y : ");
    scanf("%d %d", &x, &y);

    for(i=1; i <= x && i <= y; i++){

        // Checks if i is factor of both integers
        if(x % i == 0 && y % i == 0){
            b[amount] = i; // store the gcd, lcd
            amount++;
        }
    }

    // may be forever loop, inside decrease size
    printf("Output\n");
    int totalSize = amount;
    int a, c;
    amount -= 1; // decrease the bound
    while(amount >= 0){
        a = x / b[amount];
        c = y / b[amount];
        printf("(%d,%d,%d)\n", a, b[amount], c);
        amount -= 1;
    }
    printf("total = %d\n", totalSize);

    return 0;
}