#include "eshop.h"
#include "customer.h"

int main() {
	int to_eshop[NUM_CUSTOMERS][2];
	int from_eshop[NUM_CUSTOMERS][2];
	pid_t pids[NUM_CUSTOMERS];

	// Initialize pipes
    setup_pipes(to_eshop, from_eshop);

    // Fork processes
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            // Child process: Customer
            run_customer(i, to_eshop[i], from_eshop[i]);
            exit(0);
        }
    }

    // Parent process: E-Shop
    run_eshop(to_eshop, from_eshop, NUM_CUSTOMERS);

    // Wait for children to finish
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        wait(NULL);
    }

    return 0;
}
