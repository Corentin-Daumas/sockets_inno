all:
		chmod 777 *
		gcc client.c -o client
		gcc server.c -o server
		gcc encoding_test.c -o encoding_test

