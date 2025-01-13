#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "eshop.h"
#include "customer.h"

#define NUM_CUSTOMERS 5

int main() {
	initialize_catalog();

	int total_successful_purchases = 0;
	float total_revenue = 0;

	for (int i = 0; i < NUM_CUSTOMERS; i++) {
		int request_pipe[2], response_pipe[2], result_pipe[2];
		if (pipe(request_pipe) == -1 || pipe(response_pipe) == -1 || pipe(result_pipe) == -1) {
			perror("Pipe creation failed");
			exit(1);
		}

		pid_t pid = fork();
		if (pid == 0) {                      // Child process
			customer_process(i, request_pipe, response_pipe, result_pipe);
			exit(0);
		} else if (pid > 0) {                // Parent process
			printf("Parent handles the e-shop with PID %d.\n\n", getpid());
			

			close(request_pipe[1]);		// Close write end of request pipe
			close(response_pipe[0]);	// Close read end of response pipe
			close(result_pipe[1]);		// Close write end of result pipe (parent reads results)
			

			process_customer_request(request_pipe, response_pipe);

			int successful_purchases;
			float total_spent;

			// Read results from the child
			read(result_pipe[0], &successful_purchases, sizeof(int));
			read(result_pipe[0], &total_spent, sizeof(float));

			// Update totals
			total_successful_purchases += successful_purchases;
			total_revenue += total_spent;


			close(request_pipe[0]);		// Close read end of request pipe
			close(response_pipe[1]);	// Close write end of response pipe
			close(result_pipe[0]);		// Close read end of result pipe
		} else {
			perror("Fork failed");
			exit(1);
		}
	}

	printf("Out of %d orders made, %d were sucessful.\n", NUM_CUSTOMERS * NUM_ORDERS, total_successful_purchases);
	printf("Grand total revenue: %.2f EUR\n", total_revenue);

	return 0;
}
