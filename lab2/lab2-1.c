// Natthapong Lueangphumphitthaya 63011208

#include <stdio.h>

int main() {
    float accNum = 0;
    float num = 0;
    int size = 0;

    while(1){
        printf("To quit, enter 0 for number\n");
        printf("Number = ? ");

        scanf("%f", &num);

        if(num == 0){
            break;
        }

        accNum += num;
        size += 1;

        
    }
    printf("sum = %d", (int) accNum);
    printf("\naverage = %f", accNum / size);
    printf("\n");


    return 0;
}