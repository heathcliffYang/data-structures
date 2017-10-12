CC = gcc
CFLAGS = -std=gnu11 -Wall -g
OBJS = linked_list.o tree.o main.o

.PHONY: all clean test

deps := $(OBJS:%.o=.%.o.d)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -MMD -MF .$@.d -c $<

demo: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -rdynamic
