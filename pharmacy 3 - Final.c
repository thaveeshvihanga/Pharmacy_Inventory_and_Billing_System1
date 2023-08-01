#include <stdio.h>
#include <string.h>
#include <time.h>

// Constants
#define MAX_PRODUCTS 1000
#define MAX_SUPPLIERS 1000


// Define structures to represent product and supplier information
struct Product {
    char name[100];
    char generic_name[100];
    int batch_number;
    char expiry_date[20];
    int quantity;
    float price;
};

struct Supplier {
    char name[100];
    char contact_details[100];
    char terms[100];

};

//load data from file
void loadData(struct Product inventory[], int *productCount, struct Supplier suppliers[], int *supplierCount) {
    FILE* file = fopen("inventory_data.txt", "r");

    if (file == NULL) {
        printf("Error opening the file for loading data.\n");
        return;
    }

    // Read product count
    fscanf(file, "Product Count: %d\n", productCount);

    // Read product data
    for (int i = 0; i < *productCount; i++) {
        fscanf(file, "Product Name: %[^\n]\n", inventory[i].name);
        fscanf(file, "Generic Name: %[^\n]\n", inventory[i].generic_name);
        fscanf(file, "Batch Number: %d\n", &inventory[i].batch_number);
        fscanf(file, "Expiry Date: %[^\n]\n", inventory[i].expiry_date);
        fscanf(file, "Quantity: %d\n", &inventory[i].quantity);
        fscanf(file, "Price: %f\n", &inventory[i].price);
    }

    // Read supplier count
    fscanf(file, "Supplier Count: %d\n", supplierCount);

    // Read supplier data
    for (int i = 0; i < *supplierCount; i++) {
        fscanf(file, "Supplier Name: %[^\n]\n", suppliers[i].name);
        fscanf(file, "Contact Details: %[^\n]\n", suppliers[i].contact_details);
        fscanf(file, "Terms: %[^\n]\n", suppliers[i].terms);
    }

    fclose(file);
}


// Function to add a new product to the inventory
void addProduct(struct Product inventory[], int *productCount) {
    if (*productCount >= MAX_PRODUCTS) {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }

    printf("************************************************************************************************************\n\n");
    printf("                                                      Add New Product                                           \n\n");

    int choice;
    do {
        // Prompt the user to enter product details
        printf("\nEnter product name: ");
        scanf(" %[^\n]", inventory[*productCount].name);

        printf("Enter generic name: ");
        scanf(" %[^\n]", inventory[*productCount].generic_name);

        printf("Enter batch number: ");
        scanf("%d", &inventory[*productCount].batch_number);

        printf("Enter expiry date: ");
        scanf(" %[^\n]", inventory[*productCount].expiry_date);

        printf("Enter quantity: ");
        scanf("%d", &inventory[*productCount].quantity);

        printf("Enter price: ");
        scanf("%f", &inventory[*productCount].price);

        (*productCount)++;


        printf("Product added successfully.\n");

        // Ask the user if they want to add more products
        printf("Do you want to add more products? (1: Yes / 0: No): ");
        scanf("%d", &choice);
    } while (choice == 1);


}

// Function to track stock levels and generate alerts
void trackStock(struct Product inventory[], int productCount) {
    printf("************************************************************************************************************\n\n");
    printf("\n                                             Stock Alert                                                  \n\n");
    printf("\nProducts with low stock levels:\n");

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].quantity < 10) {
            printf("\n\nProduct: %s (Batch Number: %d)\n", inventory[i].name, inventory[i].batch_number);
        }
    }

    printf("\n************************************************************************************************************\n");
}

// Function to view the remaining inventory

void viewInventory(struct Product inventory[], int productCount, struct Supplier suppliers[]) {

    printf("************************************************************************************************************\n\n");
    printf("                                           Suwajaya Pharmacy - Inventory                                    \n\n");
    printf("************************************************************************************************************\n\n");
    printf("Product Name       | Batch Number | Quantity | Total Value (Rs.)\n");
    printf("\n------------------------------------------------------------------------------------------------------------\n");

    float totalValue = 0.0;

    for (int i = 0; i < productCount; i++) {
        int batchNumber = inventory[i].batch_number;
        char* productName = inventory[i].name;
        int quantity = inventory[i].quantity;
        float itemValue = quantity * inventory[i].price;

        printf("%-20s | %-12d | %-8d | %-16.2f\n", productName, batchNumber, quantity, itemValue);
        totalValue += itemValue;
    }

    printf("\n--------------------------------------------------------------------------------------------------------------\n");
    printf("Total Value (All Products)                           | %-16.2f\n", totalValue);
    printf("\n************************************************************************************************************\n\n");
}



// Function to add a new supplier to the supplier database
void addSupplier(struct Supplier suppliers[], int *supplierCount) {
    if (*supplierCount >= MAX_SUPPLIERS) {

    printf("\n************************************************************************************************************\n\n");
    printf("\n                              Supplier database is full. Cannot add more suppliers.                           \n");
        return;
    }

    // Prompt the user to enter supplier details
    printf("\n************************************************************************************************************\n\n");
    printf("                                             Enter Supplier Detailes                                          \n\n");
    printf("\nEnter supplier name: ");
    scanf(" %[^\n]", suppliers[*supplierCount].name);

    printf("Enter contact details: ");
    scanf(" %[^\n]", suppliers[*supplierCount].contact_details);

    printf("Enter terms: ");
    scanf(" %[^\n]", suppliers[*supplierCount].terms);


    // Increment the supplier count
    (*supplierCount)++;

    printf("                                            Supplier added successfully.                                        \n");
}



// Function to search for products by name or batch number
void searchProduct(struct Product inventory[], int productCount) {
    char searchQuery[100];
    int found = 0; // Flag to indicate if a matching product is found

    printf("\n************************************************************************************************************\n\n");
    printf("                                                  Product Search                                              \n\n");
    printf("\nEnter product name or batch number to search: ");
    scanf(" %[^\n]", searchQuery);

    // Check if the search query is empty
    if (strlen(searchQuery) == 0) {

        printf("Invalid search query. Please enter a valid product name or batch number.\n");
        return;
    }
    printf("\n************************************************************************************************************\n\n");
    printf("                                              Product Search Results                                          \n\n");
    for (int i = 0; i < productCount; i++) {

        // Check if the search query matches the product name or batch number (case-insensitive)
        if (strcasecmp(searchQuery, inventory[i].name) == 0 || atoi(searchQuery) == inventory[i].batch_number) {
            printf("Product: %s\n", inventory[i].name);
            printf("Generic Name: %s\n", inventory[i].generic_name);
            printf("Batch Number: %d\n", inventory[i].batch_number);
            printf("Expiry Date: %s\n", inventory[i].expiry_date);
            printf("Quantity: %d\n", inventory[i].quantity);
            printf("\n------------------------------------------------------------------------------------------------------------\n");
            found = 1; // Set the flag to indicate a match is found
        }
    }

    if (!found) {
        printf("\n                                         No matching products found.                                      \n");
    }

    printf("\n************************************************************************************************************\n\n");

}

// Function to handle sales, generate invoices, and issue receipts
void Salesandinvoice(struct Product inventory[], int productCount, struct Supplier suppliers[], int supplierCount) {
    const char* paymentMethods[] = {"Cash", "Credit Card"};
    int paymentMethodChoice;
    float totalPrice = 0.0;
    int productFound = 0;

    // Display a welcome message and initialize the receipt details

    printf("\n************************************************************************************************************\n\n");
    printf("\n\033[1m                                         Suwajaya Pharmacy                                            \033[0m\n\n");
    printf("************************************************************************************************************\n\n");
    printf("\n                                                    sales Invoice.                                          \n");

    do {
        char productName[100];
        int quantity;
        int foundProductIndex = -1;

        // Prompt the user to enter the product name and quantity
        printf("\nEnter product name (or 'N' to finish): ");
        scanf(" %[^\n]", productName);

        // Check if the user entered "N" to finish adding products
        if (strcasecmp(productName, "N") == 0) {
            break;
        }

        printf("Enter quantity to purchase: ");
        scanf("%d", &quantity);

        // Find the product in the inventory and get its supplier details
        for (int i = 0; i < productCount; i++) {
            if (strcasecmp(productName, inventory[i].name) == 0) {
                foundProductIndex = i;
                break;
            }
        }

        if (foundProductIndex == -1 || quantity > inventory[foundProductIndex].quantity || quantity <= 0) {
            printf("Invalid product name or quantity. Please try again.\n");
            continue; // Go back to the beginning of the loop to re-enter the product details
        } else {
            // Calculate the total price for the purchase of this item
            float itemPrice = quantity * inventory[foundProductIndex].price;
            totalPrice += itemPrice;
            productFound = 1;

            // Display the product details for the current item
            printf("\n************************************************************************************************************\n\n");
            printf("\n\033[1m                                         Suwajaya Pharmacy                                            \033[0m\n\n");
            printf("\n                                                 Item Details                                             \n");
            printf("\nProduct: %s\n", inventory[foundProductIndex].name);
            printf("Quantity: %d\n", quantity);
            printf("Unit Price: Rs.%.2f\n", inventory[foundProductIndex].price);
            printf("Total Price for this Item: Rs.%.2f\n", itemPrice);
            printf("\n************************************************************************************************************\n\n");

            // Update the inventory by deducting the sold quantity
            inventory[foundProductIndex].quantity -= quantity;
        }
    } while (1);

    if (!productFound) {
        printf("\n                                             No items added to the invoice.                                        \n");
        return;
    }

    // Prompt the user to select a payment method
    printf("\nSelect Payment Method:\n");
    for (int i = 0; i < 2; i++) {
        printf("%d. %s\n", i + 1, paymentMethods[i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &paymentMethodChoice);

    // Check if the selected payment method is valid
    if (paymentMethodChoice < 1 || paymentMethodChoice > 2) {
        printf("Invalid payment method choice.\n");
        return;
    }

    printf("\nPayment Method: %s\n", paymentMethods[paymentMethodChoice - 1]);
    printf("\n                                  Payment successful. Thank you for your purchase!                            \n");

    // Generate and issue the receipt
    time_t now;
    time(&now);
    struct tm* timeInfo = localtime(&now);
    static int receiptCounter = 1;

    printf("\n\033[1m                                         Suwajaya Pharmacy                                     \033[0m");
    printf("\n                                            No.256,Kotte Road,Nugegoda                                    \n\n");
    printf("************************************************************************************************************\n\n\n");

    printf("Receipt Number: %d\n", receiptCounter++);
    printf("Date and Time: %02d/%02d/%d %02d:%02d\n", timeInfo->tm_mday, timeInfo->tm_mon + 1, timeInfo->tm_year + 1900, timeInfo->tm_hour, timeInfo->tm_min);
    printf("Total Amount: Rs.%.2f\n", totalPrice);
    printf("Payment Method: %s\n", paymentMethods[paymentMethodChoice - 1]);
    printf("Thank you for your purchase!\n");
    printf("\n************************************************************************************************************\n\n");
}





// Function to process product returns and refunds
void handleReturns(struct Product inventory[], int productCount) {
    char productName[100];
    int returnedQuantity;

    // Prompt the user to enter the product name and quantity returned
    printf("************************************************************************************************************\n\n");
    printf("                                                    Product Return                                            \n\n");
    printf("\nEnter product name for return: ");
    scanf(" %[^\n]", productName);

    printf("Enter quantity returned: ");
    scanf("%d", &returnedQuantity);

    // Find the product in the inventory and update the quantity
    int foundProductIndex = -1;
    for (int i = 0; i < productCount; i++) {
        if (strcasecmp(productName, inventory[i].name) == 0) {
            foundProductIndex = i;
            break;
        }
    }

    if (foundProductIndex == -1 || returnedQuantity <= 0) {
        printf("                                     Invalid product name or quantity for return.                         \n");
        return;
    }

    inventory[foundProductIndex].quantity += returnedQuantity;

    printf("\n                                     Product return processed successfully.                                 \n");
}

// Function to generate sales reports
void generateSalesReport(struct Product inventory[], int productCount, struct Supplier suppliers[], int supplierCount) {

    printf("************************************************************************************************************\n\n");
    printf("                                                  Sales Report                                              \n\n");

    // Print the table header
    printf("%-20s | %-12s | %-10s | %-16s | %-12s\n", "Product", "Batch Number", "Quantity", "Price Per Unit", "Total Revenue");
    printf("\n\n---------------------------------------------------------------------------------------------------------\n\n");

    // Variables to store total sales and revenue
    int totalSales = 0;
    float totalRevenue = 0.0;

    for (int i = 0; i < productCount; i++) {
        int productSales = inventory[i].quantity; // Assuming each sold item represents a sale
        float productRevenue = productSales * inventory[i].price;

        printf("%-20s | %-12d | %-10d | Rs.%-15.2f | Rs.%-12.2f\n", inventory[i].name, inventory[i].batch_number, productSales, inventory[i].price, productRevenue);

        // Accumulate the total sales and revenue
        totalSales += productSales;
        totalRevenue += productRevenue;
    }

    printf("\n-----------------------------------------------------------------------------------------------------------\n\n");
    printf("%-20s | %-12s | %-10d | %-16s | Rs.%-12.2f\n", "Overall Total", "", totalSales, "", totalRevenue);
    printf("\n\n***********************************************************************************************************\n");
}

void saveData(struct Product inventory[], int productCount, struct Supplier suppliers[], int supplierCount) {
    FILE* file = fopen("inventory_data.txt", "w");

    if (file == NULL) {
        printf("Error opening the file for saving data.\n");
        return;
    }

    // Save inventory data
    fprintf(file, "Product Count: %d\n", productCount);
    for (int i = 0; i < productCount; i++) {
        fprintf(file, "Product Name: %s\n", inventory[i].name);
        fprintf(file, "Generic Name: %s\n", inventory[i].generic_name);
        fprintf(file, "Batch Number: %d\n", inventory[i].batch_number);
        fprintf(file, "Expiry Date: %s\n", inventory[i].expiry_date);
        fprintf(file, "Quantity: %d\n", inventory[i].quantity);
        fprintf(file, "Price: %.2f\n", inventory[i].price);
    }

    // Save supplier data
    fprintf(file, "Supplier Count: %d\n", supplierCount);
    for (int i = 0; i < supplierCount; i++) {
        fprintf(file, "Supplier Name: %s\n", suppliers[i].name);
        fprintf(file, "Contact Details: %s\n", suppliers[i].contact_details);
        fprintf(file, "Terms: %s\n", suppliers[i].terms);
    }

    fclose(file); // Add the closing parenthesis here
}


int main() {
    // Define arrays to hold product and supplier data
    struct Product inventory[MAX_PRODUCTS];
    struct Supplier suppliers[MAX_SUPPLIERS];

    // Initialize variables to keep track of the number of products and suppliers
    int productCount = 0;
    int supplierCount = 0;

    loadData(inventory, &productCount, suppliers, &supplierCount);

    // Implement the main program loop where users can interact with the system
    int choice;
    do {
        // Get the current date and time
        time_t now;
        struct tm *localTime;
        char dateStr[128];
        char TimeStr[128];

        time(&now);
        localTime = localtime(&now);

        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", localTime);
        strftime(TimeStr, sizeof(TimeStr), "%H:%M:%S", localTime);

        // Display a menu of options for the user
        printf("************************************************************************************************************\n");
        printf("\n                                Pharmacy Inventory and Billing System                                     ");
        printf("\n\033[1m                                         Suwajaya Pharmacy                                     \033[0m");
        printf("\n                                     No.256,Kotte Road,Nugegoda                                    \n\n");
        printf("************************************************************************************************************\n\n");

        // Display the current date and time
        printf(" Date     : %s\n", dateStr);
        printf(" Time     : %s\n", TimeStr);
        printf(" Location : Nugegoda, Sri Lanka\n\n\n");


        printf("1. Add Product\n");
        printf("2. View Inventory\n");
        printf("3. Track Stock\n");
        printf("4. Add Supplier\n");
        printf("5. Search Product\n");
        printf("6. Sales Invoice\n");
        printf("7. Sales Returns\n");
        printf("8. Generate Sales Report\n");
        printf("0. Exit\n");
        printf("\n* Please Don't Close the program USE EXIT button \n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        // Use a switch statement to execute the chosen option
        switch (choice) {
            case 1:
                addProduct(inventory, &productCount);
                break;
            case 2:
                viewInventory(inventory, productCount, suppliers);
                break;
            case 3:
                trackStock(inventory, productCount);
                break;
            case 4:
                addSupplier(suppliers, &supplierCount);
                break;
            case 5:
                searchProduct(inventory, productCount);
                break;
            case 6:
                Salesandinvoice(inventory, productCount, suppliers, supplierCount);
                break;
            case 7:
                handleReturns(inventory, productCount);
                break;
            case 8:
                generateSalesReport(inventory, productCount, suppliers, supplierCount);
                break;
            case 0:
                printf("\n                                         Exiting the program...                                \n");
                saveData(inventory, productCount, suppliers, supplierCount); // Save the data before exiting
                break;
            default:
                printf("\n                                    Invalid choice. Please try again.                           \n");
                break;
        }
    } while (choice != 0);

    return 0;
}
