
#include <stdio.h>
#include <math.h>

int main() {
    unsigned long n; // need to use %lu instead of %ld
    printf("*** Display integer in different styles ***\n");
    printf("Enter an integer : ");
    scanf("%lu", &n);
    printf("Your number : %lu", n);
    printf("\nvariable size = %lu bytes", sizeof(n));

    int accDigit[4];
    // unsigned long accDigit[4];
    // char commaFormat[13];
    for(int i = 0; i < 4; i++){
        accDigit[i] = n % 1000;

        if(i == 0){
            printf("\nlast 3 digits : %d", accDigit[i]);
        }
        else{
            printf("\nnext 3 digits : %d", accDigit[i]);
        }

        n = floor(n / 1000);

    }
    printf("\ncomma format : ");
    for(int i = 3; i >= 0; i--){
        if(i == 0){
            printf("%d", accDigit[i]);
        }
        else{
            printf("%d,", accDigit[i]);
        }
    }
    printf("\n");

    // test case 1 = 1234567890
    // test case 2 = 1222333444
    // test case 3 = 3456789712
    



    return 0;
}