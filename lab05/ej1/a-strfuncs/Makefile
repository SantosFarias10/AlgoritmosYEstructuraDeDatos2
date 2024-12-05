CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c99
CNAME = strings

all: compilar

main.o: main.c
	gcc $(CFLAGS) -c main.c

strfuncs.o: strfuncs.c
	gcc $(CFLAGS) -c strfuncs.c

compilar: main.o strfuncs.o
	gcc $(CFLAGS) *.o -o $(CNAME)

valg: $(CNAME)
	valgrind --leak-check=full -s ./$(CNAME)

clean:
	rm -f *.o $(CNAME)

.PHONY: clean
