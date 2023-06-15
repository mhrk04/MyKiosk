#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    struct Item currentItem;

    while (fread(&currentItem, sizeof(struct Item), 1, transactionFile)) {
        printf("%-6s | %-8d\n", currentItem.code, currentItem.quantity);
        printf("------------------------\n");
    }

    fclose(transactionFile);
}

int main() {
  system("cls");
    displaySoldItems();
    printf("Press ENTER to go back to the menu");
    getchar();
    return 0;
}