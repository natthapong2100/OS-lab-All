#include <stdio.h>
#include <math.h>

int main(){
    int num;
    printf("Enter a positive number : ");
    scanf("%d", &num); // may be check num from % by round
    int accNum[100];
    int amount = 0, r;
    int fullSize = 0;
    int result = 0;
    int digitNum = 0;

    while(num > 0){
        r = num % 10;
        num = floor(num / 10);

        accNum[amount] = r;
        result += accNum[amount];
        amount++;
        digitNum++;

        if(digitNum > 9){
            printf("The number of digit is exceed 9 digits. Cannot calculate!\n");
            break;
        }

        if(num <= 0){
            amount -= 1;
            while(amount >= 0){
                if(amount == 0){
                    printf("%d = %d", accNum[amount], result);

                    if(result >= 10){
                        num = result; // new
                        result = 0;
                        printf(" => ");
                    }
                    else{
                        printf("\n");
                    }
                    
                }
                else{
                    printf("%d + ", accNum[amount]);
                }
                amount -= 1;
            }
            amount = 0;

        }
    }

    return 0;
}