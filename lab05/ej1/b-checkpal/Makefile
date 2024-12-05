CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c99
CNAME = palcheck

all: compilar

objetos:
	gcc $(CFLAGS) -c *.c

compilar: objetos
	gcc $(CFLAGS) *.o -o $(CNAME)

valg: $(CNAME)
	valgrind --leak-check=full -s ./$(CNAME)

clean:
	rm -f *.o $(CNAME)

.PHONY: clean
