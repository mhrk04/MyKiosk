#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ITEMS 20

struct Item {
    char code[6];
    int quantity;
};

struct KioskItem {
    char code[6];
    char name[12];
    int stock;
    int lowLimit;
    double costPrice;
    double sellingPrice;
};

double calculateProfit(struct KioskItem* kioskItems, int numItems, struct Item* soldItems, int numSoldItems) {
    double totalProfit = 0.0;

    for (int i = 0; i < numSoldItems; i++) {
        for (int j = 0; j < numItems; j++) {
            if (strcmp(soldItems[i].code, kioskItems[j].code) == 0) {
                double profit = (kioskItems[j].sellingPrice - kioskItems[j].costPrice) * soldItems[i].quantity;
                totalProfit += profit;
                break;
            }
        }
    }

    return totalProfit;
}

void displaySoldItems() {
    time_t currentTime = time(NULL);

    // Convert the current time to a string
    char* dateString = ctime(&currentTime);

    // Print the current date
    printf("Current date: %s\n", dateString);

    printf("Items Sold:\n");
    printf("Code   |  Quantity Sold\n");
    printf("------------------------\n");

    FILE* transactionFile = fopen("transactions.bin", "rb");
    if (transactionFile == NULL) {
        printf("Error opening transaction file!\n");
        return;
    }

    struct Item soldItems[MAX_ITEMS];
    int numItems = 0;

    // Read all the sold items into an array
    while (fread(&soldItems[numItems], sizeof(struct Item), 1, transactionFile)) {
        numItems++;
    }

    fclose(transactionFile);

    // Load kiosk items from the database
    FILE* kioskFile = fopen("myKdata.ori", "rb");
    if (kioskFile == NULL) {
        printf("Error opening kiosk database file!\n");
        return;
    }

    struct KioskItem kioskItems[MAX_ITEMS];
    int numKioskItems = 0;

    // Read all the kiosk items into an array
    while (fread(&kioskItems[numKioskItems], sizeof(struct KioskItem), 1, kioskFile)) {
        numKioskItems++;
    }

    fclose(kioskFile);

    // Print the sold items in reverse order (latest transaction at the top)
    for (int i = numItems - 1; i >= 0; i--) {
        printf("%-6s | %-8d\n", soldItems[i].code, soldItems[i].quantity);
        printf("------------------------\n");
    }

    // Calculate and print the total profit
    double totalProfit = calculateProfit(kioskItems, numKioskItems, soldItems, numItems);
    printf("Total Profit: %.2lf\n", totalProfit);
}

int main() {
    system("cls");
    displaySoldItems();
    printf("Press ENTER to go back to the menu");
    getchar();
    return 0;
}
