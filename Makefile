CC = gcc
CFLAGS = -Wall -g

all: main

main: main.o eshop.o customer.o
	$(CC) $(CFLAGS) -o main main.o eshop.o customer.o

main.o: main.c eshop.h customer.h
	$(CC) $(CFLAGS) -c main.c

eshop.o: eshop.c eshop.h
	$(CC) $(CFLAGS) -c eshop.c

customer.o: customer.c customer.h
	$(CC) $(CFLAGS) -c customer.c

clean:
	rm -f *.o main
