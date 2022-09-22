// Natthapong Lueangphumphitthaya 63011208

#include <stdio.h>
int main() {
    int choice;
    int r;
    float area, perimeter;
    const float PI = 22.0/7.0;

    while(1){
        printf("\n1. Area\n2. Perimeter\n0. Exit\n");

        printf("\nYour Selection => ");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Enter radius: ");
            scanf("%d", &r);
            area = PI * (r * r);
            printf("area = %f", area);
        }
        else if(choice == 2){
            printf("Enter radius: ");
            scanf("%d", &r);
            perimeter = 2 * PI * r;
            printf("perimeter = %f", perimeter);
        }
        else if(choice == 0){
            printf("Good Bye");
            printf("\n");
            break;
        }    
    }

    return 0;
}