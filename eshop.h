#ifndef ESHOP_H
#define ESHOP_H

#define PRODUCT_COUNT 20

typedef struct {
	char description[50];	// Product name or description
	float price;		// Price of the product
	int item_count;		// Number of available items
} Product;

extern Product catalog[PRODUCT_COUNT];	// Declare the catalog array

// Function declarations
void initialise_catalog();
void process_customer_request(int request_pipe[2], int response_pipe[2]);

#endif // ESHOP_H
