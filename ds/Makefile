# queue/Makefile

CC = clang
AR = ar
ARFLAGS = rcs

SRC = queue.c stack.c
OBJ = $(SRC:.c=.o)
LIB = libds.a

CFLAGS = -Wall -I.

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a
