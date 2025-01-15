#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "customer.h"

void customer_process(int customer_id, int request_pipe[2], int response_pipe[2]) {
	printf("Starting Customer #%d with PID %d and PPID %d.\n", customer_id + 1, getpid(), getppid());

	close(request_pipe[0]);		// Close read end of request pipe
	close(response_pipe[1]);	// Close write end of response pipe

	srand(time(NULL) ^ (getpid() << 16));		// Seed the random generator
	
	for (int i = 0; i < NUM_ORDERS; i++) {
		int product_index = rand() % PRODUCT_COUNT;	// Random product index
		write(request_pipe[1], &product_index, sizeof(int));	// Send product order
		write(request_pipe[1], &customer_id, sizeof(int));	// Send customer's id

		float price;
		char description[50];
		read(response_pipe[0], &price, sizeof(float));	// Read cost of product bought/error
		read(response_pipe[0], description, sizeof(description));	// Read description of product

		if (price == -1) {
			// If price is negative, order was not possible
			printf("Customer #%d: %s is out of stock.\n", customer_id + 1, description);
		} else {
			printf("Customer #%d: Bought %s for %.2f.\n", customer_id + 1, description, price);
		}

		sleep(1);	// Wait for 1 second
	}

	close(request_pipe[1]);		// Close write end of request pipe
	close(response_pipe[0]);	// Close read end of response pipe
	exit(0);
}
