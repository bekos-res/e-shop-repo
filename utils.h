#ifndef UTILS_H
	#define UTILS_H
	#include "eshop.h"

	#define NUM_PRODUCTS 7
	#define NUM_CUSTOMERS 5

	void initialise_random();
	int generate_random_product(int num_products);
	void initialise_catalog(Product catalog[], int num_products);
	void setup_pipes(int to_eshop[][2], int from_eshop[][2]);

#endif // UTILS_H
