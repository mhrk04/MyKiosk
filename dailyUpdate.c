#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ITEMS 20

struct Item {
    char code[6];
    int quantity;
};

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

    // Print the sold items in reverse order (latest transaction at the top)
    for (int i = numItems - 1; i >= 0; i--) {
        printf("%-6s | %-8d\n", soldItems[i].code, soldItems[i].quantity);
        printf("------------------------\n");
    }
}


int main() {
  system("cls");
    displaySoldItems();
    printf("Press ENTER to go back to the menu");
    getchar();
    return 0;
}