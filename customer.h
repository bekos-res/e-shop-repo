#ifndef CUSTOMER_H
#define CUSTOMER_H

#define NUM_ORDERS 10

void customer_process(int customer_id, int request_pipe[2], int response_pipe[2], int result_pipe[2]);

#endif // CUSTOMER_H
