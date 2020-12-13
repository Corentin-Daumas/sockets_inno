#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8096


typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

/* On utilisera le mode connecte car plus simple
pas besoin de refaire la connexion a chaque fois */

int sock_s, conn;
char message[100]; 
SOCKADDR_IN address;

int adressLen = sizeof(address); 

int main(int argc, char const *argv[]) {

	address.sin_family = AF_INET; /* protocole internet */
	address.sin_addr.s_addr = htonl(INADDR_ANY); /* toutes les addresses IP de la station (adresse de l'hote) 
	pour specifier l'adresse a utiliser: inet_adr("127.0.0.1"); */
	address.sin_port = htons(PORT); /* designe le port utilise */

	/* AF_INET: pour TCP/IP, adresse internet sur 4 octets:
	adresse IP et num. de port pour pouvoir avoir plusieurs sockets sur une meme machine
	SOCK_STREAM: service oriente connexion, comm. par flot de donnees (un seul bloc)
	protocole = 0: car pas utile en TCP/IP */
	sock_s = socket(AF_INET, SOCK_STREAM, 0);

	bind(sock_s, (SOCKADDR *)&address, sizeof(address)); /* bind de la socket */

	listen(sock_s, 5); /* place un socket en attente de connexion 
	le 5 represente le nbr de connexion max pouvant etre lu en attente */

/*------------Test forking------------------*/
	while(conn = accept(sock_s, (SOCKADDR *)&address, &adressLen)) {
	/* permet la connexion en acceptant un appel 
	sock_s: socket precedemment ouvert
	&address: tampon qui stocke l'adresse de l'appelant
	&adressLen: taille de l'adresse de l'appelant */ 
	    int enfant;
	    enfant = fork();
	    if(enfant == 0) {
	        while (recv(conn, message, 100, 0)>0) {
	            printf("%d : %s\n", conn, message);

	            write(conn, message, sizeof(message));
	            listen(conn, 1);

	            memset (message, 0, sizeof (message));
	        }
	        exit(0);
	    }
	}
}