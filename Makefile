CC = gcc
CFLAGS = -Wall -g

all: main

main: main.o eshop.o customer.o utils.o
	$(CC) $(CFLAGS) -o main main.o eshop.o customer.o utils.o

main.o: main.c eshop.h customer.h utils.h
	$(CC) $(CFLAGS) -c main.c

eshop.o: eshop.c eshop.h utils.h
	$(CC) $(CFLAGS) -c eshop.c

customer.o: customer.c customer.h utils.h
	$(CC) $(CFLAGS) -c customer.c

clean:
	rm -f *.o main
