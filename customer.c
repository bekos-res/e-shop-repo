include "customer.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void run_customer(int id, int to_eshop[2], int from_eshop[2]) {
    // Close unused ends of pipes
    close(to_eshop[0]); // Close read end (customer only writes orders)
    close(from_eshop[1]); // Close write end (customer only reads responses)

    for (int i = 0; i < 10; i++) { // Send 10 orders
        int order = rand() % NUM_PRODUCTS; // Pick a random product
        write(to_eshop[1], &order, sizeof(order)); // Send order to e-shop
        printf("Customer %d: Ordered product %d\n", id, order);

        int response;
        read(from_eshop[0], &response, sizeof(response)); // Get response
        printf("Customer %d: Received response %d\n", id, response);

        sleep(1); // Wait before sending the next order
    }

    // Close pipes when done
    close(to_eshop[1]);
    close(from_eshop[0]);
}
