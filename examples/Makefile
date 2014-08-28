# Compile examples.
# @since Tue Aug 26 20:38:01 EDT 2014
# @author Mark Bucciarelli <mkbucc@gmail.com>

INC=..
CFLAGS=-Wall -I${INC}

all: slist slistofslists

%: %.c  ${INC}/queue.h
	$(CC) $(CFLAGS) -o $@ $@.c

clean:
	rm -f slist slistofslists
