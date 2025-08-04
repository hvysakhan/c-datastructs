
# Makefile in the root directory

CC = clang
CFLAGS = -Wall -Ids
LDFLAGS = -Lds -lds

SRC = main.c
OBJ = $(SRC:.c=.o)
TARGET = main

TEST_SRC = test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = test

.PHONY: all clean ds

all: ds $(TARGET) test

# Build the main binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


# Build the test binary
$(TEST_TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Build static library in ds/
ds:
	$(MAKE) -C ds

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ds clean
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET)
