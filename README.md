# E-Shop Project

This project implements a simulated e-shop system to demonstrate **Inter-Process Communication (IPC)** using **anonymous pipes** in a multi-process environment. The e-shop allows customers to place orders for products, processes these orders in real-time, and generates a detailed report summarising the activity.

## Features

1. **Product Catalog**:
   - The e-shop maintains a catalog of 20 products.
   - Each product is defined by:
     - A description
     - Price
     - Stock count (initially set to 2 units per product).
     - Attempt count (for all attempts to buy it)
     - Failed customer service list (to keep track of unserviced customers)

2. **Customer Simulation**:
   - Up to 5 customers interact with the e-shop concurrently.
   - Each customer places 10 product orders at 1-second intervals.

3. **Order Processing**:
   - The e-shop processes orders sequentially, taking 1 second per order.
   - Successful purchases deduct from the stock; unsuccessful attempts notify the customer.

4. **Inter-Process Communication**:
   - Communication between the e-shop (parent process) and customers (child processes) is handled using **anonymous pipes**.
   - Two pipes are used per customer for bidirectional communication.

5. **Summary Report**:
   - After all orders are processed, the e-shop generates a report containing:
     - Product sales statistics.
     - Unserved customers (if any).
     - Total orders, successful and failed transactions, and overall revenue.

## Components

### 1. `customer.c` / `customer.h`
Defines the behavior of customer processes:
- Simulates order requests with random product selections.
- Sends order data to the e-shop and receives results.
- Handles purchase success or failure notifications.
- Collects customer results and produces customer report.

### 2. `eshop.c` / `eshop.h`
Implements the e-shop logic:
- Maintains and manages the product catalog.
- Processes customer orders, updating stock levels.
- Sends responses (success/failure) back to customers.

### 3. `main.c`
Coordinates the simulation:
- Initialises the e-shop and product catalog.
- Spawns customer processes and sets up communication pipes.
- Collects results and produces a summary report.

### 4. `Makefile`
Automates the build process:
- Compiles all components using GCC.
- Provides `make all` and `make clean` targets.

## How to Build and Run

### Prerequisites
- A Unix-like operating system (Linux, macOS).
- GCC or compatible C compiler.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/bekos-res/e-shop-repo.git
2. Change directory into repository:
   ```bash
   cd e-shop-repo
3. Make package
   ```bash
   make
4. Execute programme
   ```bash
   ./eshop
