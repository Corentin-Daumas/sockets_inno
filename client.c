#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int main(int argc, char const *argv[]) {
    int i = 0;
    int sock_c, valRead; 
    SOCKADDR_IN serv_address;
    char* msg = "Hello! c'est le client"; 
    char buffer[1024] = {0}; 

    /* declaration du message */
    char message[1024];

    sock_c = socket(AF_INET, SOCK_STREAM, 0); 

    serv_address.sin_family = AF_INET; 
    serv_address.sin_port = htons(PORT); 

	inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr);

    connect(sock_c, (struct sockaddr *)&serv_address, sizeof(serv_address));

    // printf(">>>");
    // scanf("%s", message);
    // send(sock_c, message, strlen(message), 0 );

    // valRead = read(sock_c, buffer, 1024);
    // printf("%s\n", buffer);



    while(1){
        printf(">>>");
        // scanf("%24[^]", message);
        //scanf("%s", message);
        gets(message); //fonction gets similaire à scanf() mais d'utiliser des espaces ATTENTION msg d'erreurs à corriger 

        // send(sock_c, message, strlen(message), 0 );
        write(sock_c, message, strlen(message)); /* meme chose que le send, y a juste pas les flags*/

        valRead = read(sock_c, buffer, 1024);
        printf("%s\n", buffer);
        memset (message, 0, sizeof (message));
        // printf(message[i]!="\n");
        // while(message[i]!="\n"){
        //     message[i] = '\0';
        //     i++;
        // }
    }
    return 0;
}