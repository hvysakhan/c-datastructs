
# Makefile in the root directory

CC = gcc
CFLAGS = -Wall -Ids
LDFLAGS = -Lds -lds

SRC = main.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
TARGET = main

TEST_SRC = test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = test

.PHONY: all clean ds test

all: ds $(TARGET) $(TEST_TARGET)

# Build the main binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


# Build the test binary
$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Build static library in ds/
ds:
	$(MAKE) -C ds

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ds clean
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET)

-include $(DEP)

