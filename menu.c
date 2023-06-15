#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "Functions.h"

int main() {
    int choice;


    while (1) {
        system("cls");
        printf("\n\n\n\n\n\n\t\t\t\t\t\tMyKiosk Menu\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t------------------------------\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t1. Create data of kiosk stocks\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t2. Display the current kiosk database\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t3. Sell item\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t4. Daily update\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t5. Check database for items below limit\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t0. Exit\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t------------------------------\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("\t\t\t\t\t\t%d", &choice);

        switch (choice) {
            case 1:
                system("createKioskStock.exe");
                break;
            case 2:
                system("displayKioskDatabase.exe");
                break;
            case 3:
                system("sellItem.exe");
                break;
            case 4:
                system("dailyUpdate.exe");
                break;
            case 5:
                system("checkDatabase.exe");
                break;
            case 0:
                system("cls");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}