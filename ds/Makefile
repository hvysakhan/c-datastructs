CC = gcc
AR = ar
ARFLAGS = rcs

SRC = queue.c stack.c hash_table.c named_list.c queue_any.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
LIB = libds.a

CFLAGS = $(CFLAGS_COMMON) -I.

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *.d *.a

-include $(DEP)

