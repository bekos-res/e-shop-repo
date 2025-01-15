#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "eshop.h"
#include "customer.h"

int main() {
	initialise_catalog();
	srand(time(NULL));

	for (int i = 0; i < NUM_CUSTOMERS; i++) {
		int request_pipe[2], response_pipe[2];	// Pipe declaration
		if (pipe(request_pipe) == -1 || pipe(response_pipe) == -1) {	// Pipe check
			perror("Pipe creation failed");
			exit(EXIT_FAILURE);
		}

		pid_t pid = fork();

		if (pid == -1) {
			perror("Fork failed");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {  // Child process
			customer_process(i, request_pipe, response_pipe);
		} else {	// Parent process
			printf("\n\nParent handles the e-shop with PID %d.\n", getpid());
			process_customer_request(request_pipe, response_pipe);
		}
	}

	for (int i = 0; i < NUM_CUSTOMERS; i++) {
		wait(NULL);	// Wait for all children to exit
	}
	
	int total_attempts = 0, total_success = 0;
	float total_revenue = 0.0f;

	// When all orders are completed, print the e-shop's general product report
	printf("\n\n\n");
	for (int i = 0; i < PRODUCT_COUNT; i++) {
		sleep(1);
		printf("\nProduct description: %s\n", catalog[i].description);
		printf("\tAttempted orders:\t%d\n", catalog[i].attempt_count);
		printf("\tNumber of sales:\t%d\n", catalog[i].sold_count);

		if (catalog[i].attempt_count > catalog[i].sold_count) {	// If there were more attempts than sales, someone failed
			printf("\tList of users who failed to buy \"%s\":\n", catalog[i].description);
			for (int j = 0; j < NUM_CUSTOMERS; j++) {	// For each customer who could have ordered this product
				int customer_fails = catalog[i].failed_customers[j];	// see how many times they failed to order it
				if (customer_fails > 0)	// and if there is any number other than 0 (initial number)
					printf("\t\tCustomer #%d was not serviced (%d times).\n", j, customer_fails);
				// print out the customer's ID and amount of failed requests of this product
			}
		}

		total_attempts += catalog[i].attempt_count;
		total_success += catalog[i].sold_count;
		total_revenue += catalog[i].sold_count * catalog[i].price;
	}

	// General e-shop order report at the end
	printf("\n\n");
	printf("\nSummary:\n");
	printf("\tTotal Attempts: %d\n", total_attempts);
	printf("\tTotal Successful Purchases: %d\n", total_success);
	printf("\tTotal Revenue: %.2f EUR\n", total_revenue);

	return 0;
}
