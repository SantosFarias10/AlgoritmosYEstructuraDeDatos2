CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c99
CNAME = clone

all: compilar

compilar:
	gcc $(CFLAGS) clone.c -o $(CNAME)

valg: $(CNAME)
	valgrind --leak-check=full -s ./$(CNAME)

clean:
	rm -f *.o $(CNAME)

.PHONY: clean
