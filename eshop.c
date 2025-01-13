#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "eshop.h"

Product catalog[PRODUCT_COUNT];	// Define the catalog array

void initialize_catalog() {
	for (int i = 0; i < PRODUCT_COUNT; i++) {
		snprintf(catalog[i].description, 50, "Product %d", i + 1);
		catalog[i].price = (float)(10 + (rand() % 91));	// Random price between 10 and 100
		catalog[i].item_count = 2;	// Default: 2 items in stock
	}
}

void process_customer_request(int request_pipe[2], int response_pipe[2]) {
	close(request_pipe[1]);		// Close write end of request pipe
	close(response_pipe[0]);        // Close read end of response pipe

	int product_index;
	while (read(request_pipe[0], &product_index, sizeof(int)) > 0) {
		if (product_index >= 0 && product_index < PRODUCT_COUNT) {
			if (catalog[product_index].item_count > 0) {
				catalog[product_index].item_count--;
				float price = catalog[product_index].price;
				write(response_pipe[1], &price, sizeof(float)); // Send success response
			} else {
				float unavailable = -1;
				write(response_pipe[1], &unavailable, sizeof(float)); // Out of stock
			}
		}
	}

	close(request_pipe[0]);                      // Close read end of request pipe
	close(response_pipe[1]);                     // Close write end of response pipe
}
