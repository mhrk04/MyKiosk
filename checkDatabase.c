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

void displayKioskDatabase() {
    struct Item item;

    FILE* file = fopen("MyKdata.ori", "rb");
    if (file == NULL) {
        printf("Error opening kiosk database file!\n");
        return;
    }

    printf("Stock Low:\n");
    printf("----------------------------------------\n");
    printf("Code    Name            Stock   Low Limit       Cost Price(RM)      Selling Price(RM)\n");
    printf("----------------------------------------\n");

    while (fread(&item, sizeof(struct Item), 1, file) == 1) {
        if (strcmp(item.code, "") != 0 && item.stock <= item.lowLimit) {
            printf("%-6s  %-12s %5d   %5d        %10.2lf          %10.2lf\n", item.code, item.name, item.stock, item.lowLimit, item.costPrice, item.sellingPrice);
        }
    }

    printf("----------------------------------------\n");

    fclose(file);
}

void updateKioskStock() {
    system("cls");
    displayKioskDatabase();

    char code[6];
    int quantity;

    printf("Update Kiosk Stock:\n");
    printf("Enter item code: ");
    scanf("%s", code);
    
    FILE* file = fopen("MyKdata.ori", "rb+");
    if (file == NULL) {
        printf("Error opening kiosk stock database!\n");
        return;
    }

    struct Item currentItem;
    int found = 0;

    while (fread(&currentItem, sizeof(struct Item), 1, file)) {
        if (strcmp(currentItem.code, code) == 0) {
            found = 1;
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            
            currentItem.stock += quantity;
            
            fseek(file, -(long int)sizeof(struct Item), SEEK_CUR);
            fwrite(&currentItem, sizeof(struct Item), 1, file);
            
            break;
        }
    }
    
    fclose(file);

    if (!found) {
        printf("Item not found!\n");
        getchar();
        return;
    }

    printf("Kiosk stock updated successfully!\n");
    getchar();
}

int main() {
    system("cls");
    displayKioskDatabase();

    char choice;

    do {
        printf("Do you want to update the kiosk stock? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            updateKioskStock();
        //     printf("Do you want to update more items? (Y/N): ");
        // scanf(" %c", &choice);
        }
    } while (choice == 'Y' || choice == 'y');
    getchar();
    return 0;
}
