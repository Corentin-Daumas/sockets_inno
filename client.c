#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int main(int argc, char const *argv[]) { 
    int sock_c, valRead; 
    SOCKADDR_IN serv_address; 
    char *msg = "Hello! c'est le client"; 
    char buffer[1024] = {0}; 

    sock_c = socket(AF_INET, SOCK_STREAM, 0); 

    serv_address.sin_family = AF_INET; 
    serv_address.sin_port = htons(PORT); 
    
	inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr);

    connect(sock_c, (struct sockaddr *)&serv_address, sizeof(serv_address));

    send(sock_c, msg, strlen(msg), 0 ); 

    valRead = read(sock_c, buffer, 1024); 
    printf("%s\n", buffer);

    return 0;
}
