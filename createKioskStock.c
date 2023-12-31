#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 20

struct Item {
    char code[6];
    char name[12];
    int stock;
    int lowLimit;
    double costPrice;
    double sellingPrice;
};

	
int isItemCodeUnique(const struct Item kioskStock[], int numItems, const char* code) {
    for (int i = 0; i < numItems; i++) {
        if (strcmp(kioskStock[i].code, code) == 0) {
            return 0;  // Item code already exists
        }
    }
    return 1;  // Item code is unique
}


void createKioskStock() {
    system("cls");
    struct Item kioskStock[MAX_ITEMS];
    int numItems = 0;
    char choice;

    FILE* file = fopen("MyKdata.ori", "wb");
    if (file == NULL) {
        printf("Error creating backup file!\n");
        return;
    }

    printf("Creating Kiosk Stock(20 MAX):\n");

    do {
        if (numItems == MAX_ITEMS) {
            printf("Maximum item limit reached. Cannot add more items.\n");
            break;
        }

        struct Item newItem;

        printf("Item %d:\n", numItems + 1);

        printf("Enter item code: ");
        scanf("%s", newItem.code);
// Check if item code already exists
        if (!isItemCodeUnique(kioskStock, numItems, newItem.code)) {
            printf("Item code already exists. Please enter a unique item code.\n");
            continue;
        }
        printf("Enter item name: ");
        scanf(" %[^\n]s", newItem.name);

        printf("Enter quantity: ");
        scanf("%d", &newItem.stock);

        printf("Enter low limit: ");
        scanf("%d", &newItem.lowLimit);

        printf("Enter cost price: ");
        scanf("%lf", &newItem.costPrice);

        newItem.sellingPrice = newItem.costPrice * 1.35; // 35% markup
        kioskStock[numItems] = newItem;
        fwrite(&newItem, sizeof(struct Item), 1, file);

        numItems++;

        printf("Do you want to add more items? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    fclose(file);

    printf("Kiosk stock created successfully!\n");
    printf("Press ENTER to go back to the menu");
    getchar();
}

int main() {
    system("cls");
    char promty;
    printf("This will rewrite current stock database. Are you sure?(Y/N)");
    scanf("%c",&promty);
    if (promty == 'Y'||promty == 'y')
    {
    createKioskStock();
    }
    return 0;
}
