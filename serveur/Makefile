all:
		chmod 777 *
		gcc client.c -o client
		gcc server.c -o server

test:
		chmod 777 *
		gcc clientTest.c -o client
		gcc serverTest.c -o server

crypt:
		chmod 777 *
		gcc -g codageRSA.c -o RSA -lm
		./RSA

#-------------------
CC=gcc
CFLAGS=-Wall -O1
LDFLAGS=  # Link Dynamic Flags (librairie)
EXEC=RSA
OBJ=crypt.o codageRSA.o
#-------------------

bind: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

$.o: %.py
	$(CC) -o -c $@ -c $<(CFLAGS)

crypt.o: crypt.py
	$(CC) -c crypt.py

codageRSA.o: codageRSA.c
	$(CC) -c codageRSA.c -lm

clean:
	rm *.o

propre: clean
	rm $(EXEC)
