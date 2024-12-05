CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c99
CNAME = starWars

all: compilar

compilar:
	gcc $(CFLAGS) clone.c -o $(CNAME)

compilar_ptr:
	gcc $(CFLAGS) clone_ptr.c -o $(CNAME)_ptr

valg: $(CNAME)
	valgrind --leak-check=full -s ./$(CNAME)

clean:
	rm -f *.o $(CNAME) $(CNAME)_ptr

.PHONY: clean
