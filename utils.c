#include "utils.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void initialise_random() {
        srand(time(NULL) + getpid());	// Seed random number generator using time and process ID
}

int generate_random_product(int num_products) {
        return rand() % num_products;	// Generate a random product index
}

// Function to initialise the product catalog
void initialise_catalog(Product catalog[], int num_products) {
        for (int i = 0; i < num_products; i++) {
        	snprintf(catalog[i].description, MAX_DESCRIPTION_LENGTH, "Product %d", i);
                catalog[i].price = (i + 1) * 2.0;	// Price as 2, 4, 6...
                catalog[i].item_count = 2;		// Each product starts with 2 items
        }
        printf("Catalog initialized with %d products.\n", num_products);
}

void setup_pipes(int to_eshop[][2], int from_eshop[][2]) {
	// Create pipes for all customers
	for (int i = 0; i < NUM_CUSTOMERS; i++) {
		if (pipe(to_eshop[i]) == -1 || pipe(from_eshop[i]) == -1) {
			perror("pipe");	// Error if pipe creation fails
			exit(EXIT_FAILURE);
		}
	}
}
