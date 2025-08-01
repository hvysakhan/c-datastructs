
# Makefile in the root directory

CC = clang
CFLAGS = -Wall -Ids
LDFLAGS = -Lds -lds

SRC = main.c
OBJ = $(SRC:.c=.o)
TARGET = main

.PHONY: all clean ds

all: ds $(TARGET)

# Build the main binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Build static library in ds/
ds:
	$(MAKE) -C ds

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ds clean
	rm -f $(OBJ) $(TARGET)
