CC		= gcc
CFLAGS		= -Wall -O2
LDFLAGS		=
SOURCES		= main.c eshop.c customer.c
HEADERS		= eshop.h customer.h
OBJECTS		= $(SOURCES:.c=.o)
EXEC		= eshop

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXEC)
