# e-shop-repo

This project simulates an e-shop with multiple customers interacting concurrently with a shared product catalog. It demonstrates inter-process communication (IPC) in a multi-process environment using pipes. The e-shop manages a catalog of products, and customers place orders for items.

## Features

1. **Product Catalog**: The e-shop maintains a catalog of 20 products, each with a description, price, and stock count.
2. **Customer Simulation**: Up to 5 customers (configurable) interact with the e-shop, placing 10 random orders each.
3. **Order Processing**: The e-shop processes each customer's requests in real-time, updating the stock count and responding to availability and pricing.
4. **Inter-Process Communication**: Uses pipes for communication between the parent process (e-shop) and child processes (customers).
5. **Concurrency**: Customers operate as separate processes, simulating a real-world e-commerce environment with multiple users.

## Components

### 1. `customer.c` / `customer.h`
Handles the customer simulation:
- Each customer makes 10 random product requests.
- If the product is available, the customer completes the purchase and the stock is updated.
- Customers send results (successful purchases and total amount spent) back to the e-shop.

### 2. `eshop.c` / `eshop.h`
Manages the e-shop:
- Initialises the product catalog with random prices and a default stock of 2 items each.
- Processes customer requests and updates stock availability.
- Responds to customers with pricing information or an out-of-stock message.

### 3. `main.c`
Orchestrates the simulation:
- Spawns child processes for each customer.
- Handles pipes for communication between the e-shop and customers.
- Aggregates and displays results, including total successful purchases and revenue.

### 4. `Makefile`
Defines the build process:
- Compiles the project using GCC.
- Includes `all` and `clean` targets for building and cleaning the project files.

## How to Build and Run

### Prerequisites
- GCC compiler
- Unix-like operating system (Linux, macOS)

### Steps:
Build and run the project:
make
./eshop
