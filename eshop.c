#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "eshop.h"

Product catalog[PRODUCT_COUNT];	// Define the catalog array

void initialise_catalog() {
	for (int i = 0; i < PRODUCT_COUNT; i++) {
		snprintf(catalog[i].description, sizeof(catalog[i].description), "Product %d", i + 1);
		catalog[i].price = 10.0f + (rand() % 91);	// Random price between 10 and 100
		catalog[i].item_count = 2;	// Default: 2 items in stock
		catalog[i].attempt_count = 0;	// No attempts initially
		catalog[i].sold_count = 0;	// No sails initially
		for (int j = 0; j < NUM_CUSTOMERS; j++) {
			catalog[i].failed_customers[j] = 0;	// No customer has failed an order on the item initially
		}
	}
}

void process_customer_request(int request_pipe[2], int response_pipe[2]) {
	close(request_pipe[1]);		// Close write end of request pipe
	close(response_pipe[0]);        // Close read end of response pipe

	int product_index;
	int customer_id;
	while (read(request_pipe[0], &product_index, sizeof(int)) > 0 && read(request_pipe[0], &customer_id, sizeof(int)) > 0) {
		if (product_index >= 0 && product_index < PRODUCT_COUNT) {
			catalog[product_index].attempt_count++;	// Increment number of attempts every time one is made

			if (catalog[product_index].item_count > 0) {	// If there is stock available...
				catalog[product_index].item_count--;	// Decrease amount of available products
				catalog[product_index].sold_count++;	// Increment counter of sold products
				float price = catalog[product_index].price;
				write(response_pipe[1], &price, sizeof(float)); // Send the price of bought product
			} else {
				catalog[product_index].failed_customers[customer_id]++;	// Register a failed order to the customer
				float unavailable = -1;
				write(response_pipe[1], &unavailable, sizeof(float)); // Out of stock
			}
			write(response_pipe[1], catalog[product_index].description, sizeof(catalog[product_index].description));
		}
	}

	close(request_pipe[0]);                      // Close read end of request pipe
	close(response_pipe[1]);                     // Close write end of response pipe
}
