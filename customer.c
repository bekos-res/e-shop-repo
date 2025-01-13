#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "customer.h"

void customer_process(int customer_id, int request_pipe[2], int response_pipe[2], int result_pipe[2]) {
	printf("Starting Customer #%d with PID %d and PPID %d.\n\n", customer_id + 1, getpid(), getppid());


	close(request_pipe[0]);		// Close read end of request pipe
	close(response_pipe[1]);	// Close write end of response pipe
	close(result_pipe[0]);		// Close read end of result pipe (child writes results)


	srand(time(NULL) ^ (getpid() << 16));		// Seed the random generator
	
	int successful_purchases = 0;
	float total_spent = 0;

	for (int i = 0; i < NUM_ORDERS; i++) {
		int product_index = rand() % 20;	// Random product index
		write(request_pipe[1], &product_index, sizeof(int));	// Send request

		float response;
		read(response_pipe[0], &response, sizeof(float));	// Read response

		if (response == -1) {
			printf("Customer #%d: Product %d is out of stock.\n", customer_id + 1, product_index);
		} else {
			successful_purchases++;
			total_spent += response;
			printf("Customer #%d: Bought Product %d for %.2f.\n", customer_id + 1, product_index, response);
		}

		sleep(1);	// Wait for 1 second
	}

	printf("Customer spent a grand total of %.2f EUR on %d successful orders out of 10 made.\n\n\n", total_spent, successful_purchases);

	// Send results back to the parent process
	write(result_pipe[1], &successful_purchases, sizeof(int));
	write(result_pipe[1], &total_spent, sizeof(float));

	close(request_pipe[1]);		// Close write end of request pipe
	close(response_pipe[0]);	// Close read end of response pipe
	close(result_pipe[1]);		// Close write end of result pipe
}
