#ifndef ESHOP_H
#define ESHOP_H

#include "customer.h"

#define NUM_CUSTOMERS 5

typedef struct {
	char description[50];	// Product name or description
	float price;		// Price of the product
	int item_count;		// Number of available items
	int attempt_count;	// Number of order attempts
	int sold_count;		// Number of successfully ordered products
	int failed_customers[NUM_CUSTOMERS];	// A checking list for failed custoner requests
} Product;

extern Product catalog[PRODUCT_COUNT];	// Declare the catalog array

// Function declarations
void initialise_catalog();
void process_customer_request(int request_pipe[2], int response_pipe[2]);

#endif // ESHOP_H
