#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080


typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

/* On utilisera le mode connecte car plus simple
pas besoin de refaire la connexion a chaque fois */

int main(int argc, char const *argv[]) { 
	int sock_s, new_socket, valRead;
	SOCKADDR_IN address;
	char buffer[1024] = {0}; 
	char *msg = "Hello! c'est le serveur";

	int adressLen = sizeof(address); 

	/* AF_INET: pour TCP/IP, adresse internet sur 4 octets:
	adresse IP et num. de port pour pouvoir avoir plusieurs sockets sur une meme machine
	SOCK_STREAM: service oriente connexion, comm. par flot de donnees (un seul bloc)
	protocole = 0: car pas utile en TCP/IP */
	sock_s = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET; /* protocole internet */
	address.sin_addr.s_addr = htonl(INADDR_ANY); /* toutes les addresses IP de la station (adresse de l'hote) 
	pour specifier l'adresse a utiliser: inet_adr("127.0.0.1"); */
	address.sin_port = htons(PORT); /* designe le port utilise */

	bind(sock_s, (SOCKADDR*)&address, sizeof(address)); /* bind de la socket */

	listen(sock_s, 10); /* place un socket en attente de connexion 
	le 10 represente le nbr de connexion max pouvant etre lu en attente */

	new_socket = accept(sock_s, (SOCKADDR*)&address, &adressLen); /* permet la connexion en acceptant un appel*/
	/* sock_s: socket precedemment ouvert
	&address: tampon qui stocke l'adresse de l'appelant
	&adressLen: taille de l'adresse de l'appelant */
	while(1){
		valRead = read(new_socket, buffer, sizeof(buffer)); /* permet la lecture dans un socket en mode connecte (TCP) */
		/* new_socket: socket precedemment ouvert
		buffer: pointeur sur un tampon qui va recevoir les octets d'un client
		sizeof(buffer): nbr d'octets lu*/
		printf("%s\n", buffer);

		send(new_socket, msg, strlen(msg), 0); /* permet d'ecrire dans une socket en mode TCP*/
		/* new_socket: socket precedemment ouvert
		msg:(buffer) tampon contenant les octets a envoyer au client
		strlen(msg): nbr d'octets a envoyer
		flags = 0: type d'envoie a adopter*/
		memset (buffer, 0, sizeof (buffer)); /* vide le buffer*/
	}
	return 0;
}