#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "eshop.h"
#include "customer.h"
#include "utils.h"

#define NUM_CUSTOMERS 3
#define EXIT_FAILURE -1

typedef int pid_t;

int main() {
	int to_eshop[NUM_CUSTOMERS][2];
	int from_eshop[NUM_CUSTOMERS][2];
	pid_t pids[NUM_CUSTOMERS];
	
	// Initialize pipes
	setup_pipes(to_eshop, from_eshop);

	// Parent process: E-Shop
	printf("Initialising the e-shop...\n");
	pid_t parent_pid = getpid();	// Get the parent's process ID
	run_eshop(to_eshop, from_eshop, NUM_CUSTOMERS);

	// Fork processes
	for (int i = 0; i < NUM_CUSTOMERS; i++) {
		if (pids[i] = fork() < 0) {
			// Error handling in case of something going wrong
			perror("Failed to make a customer...");
			exit(EXIT_FAILURE);
		} else if (pids[i] == 0) {
			// Child process succedes to be created:
			run_customer(i, to_eshop[i], from_eshop[i]);	// Customer is made with appropriate pipes.
			exit(0);	// Normal exit of child process.
		}
	}


	// Wait for children to finish
	if (getpid == parent_pid) {
		// Hard-coding logic in case of bug...
		for (int i = 0; i < NUM_CUSTOMERS; i++) {
			wait(NULL);
		}
	}

	return 0;
}
