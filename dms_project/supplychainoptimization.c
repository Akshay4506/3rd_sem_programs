#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA 1000

typedef struct {
    double sales;
    int inventory; 
} DataPoint;


void readData(DataPoint data[], int *size) {
    int valid = 0;
    while (!valid) {
        printf("Enter the number of data points: ");
        if (scanf("%d", size) == 1 && getchar() == '\n' && *size > 0 && *size <= MAX_DATA) {
            valid = 1;
        } else {
            fprintf(stderr, "Invalid number of data points. Please enter a positive integer between 1 and %d.\n", MAX_DATA);
            while (getchar() != '\n'); 
        }
    }

    printf("Enter sales and inventory data:\n");
    for (int i = 0; i < *size; i++) {
        valid = 0;
        while (!valid) {
            printf("Data point %d:\n", i + 1);
            printf("  Sales: ");
            if (scanf("%lf", &data[i].sales) == 1) {
                printf("  Inventory: ");
                if (scanf("%d", &data[i].inventory) == 1 && getchar() == '\n') {
                    if (data[i].inventory >= data[i].sales) {
                        valid = 1;
                    } else {
                        fprintf(stderr, "Error!! Inventory cannot be less than sales for data point %d.\n", i + 1);
                    }
                } else {
                    fprintf(stderr, "Invalid input for inventory. Inventory should be an integer.\n");
                    while (getchar() != '\n'); 
                }
            } else {
                fprintf(stderr, "Invalid input for sales. Sales should be a decimal number.\n");
                while (getchar() != '\n'); 
            }
        }
    }
}


double calculateMeanDouble(double arr[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}


double calculateMeanInt(int arr[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}


void calculateLinearRegression(DataPoint data[], int size, double *slope, double *intercept) {
    double sales[MAX_DATA];
    int inventory[MAX_DATA];

    for (int i = 0; i < size; i++) {
        sales[i] = data[i].sales;
        inventory[i] = data[i].inventory;
    }

    double meanSales = calculateMeanDouble(sales, size);
    double meanInventory = calculateMeanInt(inventory, size);

    double numerator = 0, denominator = 0;
    for (int i = 0; i < size; i++) {
        numerator += (sales[i] - meanSales) * (inventory[i] - meanInventory);
        denominator += pow(sales[i] - meanSales, 2);
    }

    if (denominator == 0) {
        fprintf(stderr, "Error!! Division by zero in linear regression calculation.\n");
        *slope = 0;
        *intercept = meanInventory; 
        return;
    }

    *slope = numerator / denominator;
    *intercept = meanInventory - (*slope * meanSales);
}


double predictInventory(double sales, double slope, double intercept) {
    double predicted = slope * sales + intercept;
    return round(predicted); 
}


double validateSalesInput() {
    double salesInput;
    int valid = 0;
    while (!valid) {
        printf("\nEnter sales value to predict inventory: ");
        if (scanf("%lf", &salesInput) == 1 && getchar() == '\n' && salesInput >= 0) {
            valid = 1;
        } else {
            fprintf(stderr, "Invalid sales input. Please enter a non-negative numeric value.\n");
            while (getchar() != '\n'); 
        }
    }
    return salesInput;
}

int main() {
    DataPoint data[MAX_DATA];
    int size;
    double slope, intercept;

    readData(data, &size);
    calculateLinearRegression(data, size, &slope, &intercept);

    printf("\nLinear Regression Model: Inventory = %.2f * Sales + %.2f\n", slope, intercept);

    double salesInput = validateSalesInput();
    double predictedInventory = predictInventory(salesInput, slope, intercept);

    printf("Predicted Inventory for sales %.2f: %.0f\n", salesInput, predictedInventory);

    return 0;
}
