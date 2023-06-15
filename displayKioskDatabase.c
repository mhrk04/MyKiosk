#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("Kiosk Stock Database:\n");
    printf("----------------------------------------\n");
    printf("Code    Name            Stock   Low Limit       Cost Price(RM)      Selling Price(RM)\n");
    printf("----------------------------------------\n");

    double totalRetailValue = 0.0;
    double totalCostValue = 0.0;

    while (fread(&item, sizeof(struct Item), 1, file) == 1) {
        if (strcmp(item.code, "") != 0) {
            printf("%-6s  %-12s %5d   %5d        %10.2lf          %10.2lf\n", item.code, item.name, item.stock, item.lowLimit, item.costPrice, item.sellingPrice);

            totalRetailValue += item.stock * item.sellingPrice;
            totalCostValue += item.stock * item.costPrice;
        }
    }

    printf("----------------------------------------\n");
    printf("Total Stock Retail Value RM%.2lf\n", totalRetailValue);
    printf("Total Stock Cost Value RM%.2lf\n", totalCostValue);
    printf("Profit Possible RM%.2lf\n", totalRetailValue - totalCostValue);

    fclose(file);
}

int main() {
    system("cls");
    displayKioskDatabase();
    printf("Press ENTER to go back to the menu");
    getchar();
    return 0;
}
