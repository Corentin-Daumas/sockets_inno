all:
		chmod 777 *
		gcc client.c -o client
		gcc server.c -o server
		gcc encoding_test.c -o encoding_test

test:
		chmod 777 *
		gcc -g codageRSA.c -o RSA -lm
		./RSA

#-------------------
CC=gcc
CFLAGS=-Wall -O1
LDFLAGS=  # Link Dynamic Flags (librairie)
EXEC=fact
OBJ=factorielle.o seance7.o
#-------------------

bind: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

$.o: %.c
	$(CC) -o -c $@ -c $<(CFLAGS)

factorielle.o: factorielle.c
	$(CC) -c factorielle.c

seance7.o: seance7.c
	$(CC) -c seance7.c

clean:
	rm *.o

propre: clean
	rm $(EXEC)
