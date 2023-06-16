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

struct Transaction {
    char code[6];
    int quantity;
};

void displayKioskDatabase() {
    struct Item item;

    FILE* file = fopen("MyKdata.ori", "rb");
    if (file == NULL) {
        printf("Error opening kiosk database file!\n");
        return;
    }

    printf("Kiosk Stock Database:\n");
    printf("----------------------------------------\n");
    printf("Code    Name            Stock   Low Limit      Selling Price(RM)\n");
    printf("----------------------------------------\n");

    double totalRetailValue = 0.0;
    double totalCostValue = 0.0;

    while (fread(&item, sizeof(struct Item), 1, file) == 1) {
        if (strcmp(item.code, "") != 0) {
            printf("%-6s  %-12s %5d   %5d          %10.2lf\n", item.code, item.name, item.stock, item.lowLimit, item.sellingPrice);

            
        }
    }

    printf("----------------------------------------\n");
    
    fclose(file);
}


void sellItem() {
    char code[6];
    int quantity;
    char choice;

    do {
        displayKioskDatabase();
        printf("Sell Item:\n");
        printf("Enter item code: ");
        scanf("%s", code);

        FILE* file = fopen("MyKdata.ori", "rb+");
        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }

        struct Item currentItem;
        int found = 0;
        int insufficientStock = 0;

        while (fread(&currentItem, sizeof(struct Item), 1, file)) {
            if (strcmp(currentItem.code, code) == 0) {
                found = 1;

                if (currentItem.stock == 0) {
                    printf("Insufficient stock!\n");
                    insufficientStock = 1;
                    break;
                }

                printf("Enter quantity: ");
                scanf("%d", &quantity);

                if (currentItem.stock < quantity) {
                    printf("Insufficient stock!\n");
                    insufficientStock = 1;
                    break;
                }

                currentItem.stock -= quantity;

                fseek(file, -(long int)sizeof(struct Item), SEEK_CUR);
                fwrite(&currentItem, sizeof(struct Item), 1, file);
                break;
            }
        }

        fclose(file);

        if (!found) {
            printf("Item not found!\n");
            return;
        }

        if (!insufficientStock) {
            printf("Item sold successfully!\n");

            // Save the transaction details to a binary file
            FILE* transactionFile = fopen("transactions.bin", "ab");
            if (transactionFile == NULL) {
                printf("Error opening transaction file!\n");
                return;
            }

            struct Transaction transaction;
            strcpy(transaction.code, code);
            transaction.quantity = quantity;

            fwrite(&transaction, sizeof(struct Transaction), 1, transactionFile);

            fclose(transactionFile);
        }

        printf("Do you want to sell another item? (Y/N): ");
        scanf(" %c", &choice);
        system("cls");
    } while (choice == 'Y' || choice == 'y');
}

int main() {
    system("cls");
    sellItem();
    getchar();
    printf("Press Enter to exit...");
    getchar();
    return 0;
}
