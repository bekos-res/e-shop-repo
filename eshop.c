#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "eshop.h"
#include "utils.h"

setup

void run_eshop(int to_eshop[][2], int from_eshop[][2], int num_customers) {
	int catalog[NUM_PRODUCTS] = {2}; // Initialize inventory (2 items per product)

	// Close unused ends of pipes in the parent process
	for (int i = 0; i < num_customers; i++) {
		close(to_eshop[i][1]); // Close the write end (parent only reads orders)
		close(from_eshop[i][0]); // Close the read end (parent only writes responses)
	}

	while (1) { // Process orders in a loop
		for (int i = 0; i < num_customers; i++) {
			int order;
			if (read(to_eshop[i][0], &order, sizeof(order)) > 0) {
				// Order received from customer i
				printf("E-Shop: Customer %d requested product %d\n", i, order);

				// Check inventory
				int response;
				if (catalog[order] > 0) {
					catalog[order]--; // Reduce stock	
					response = 1;    // Success
				} else {
					response = 0;    // Out of stock
				}
				sleep(1); // Simulate processing delay
				write(from_eshop[i][1], &response, sizeof(response)); // Send response
			}
		}
	}
}
