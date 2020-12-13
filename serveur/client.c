#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8096

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int sock_c, valRead; 
char message[100], message2[100];
SOCKADDR_IN serv_address;

    
int main(int argc, char const *argv[]) {

    sock_c = socket(AF_INET, SOCK_STREAM, 0); 

    serv_address.sin_family = AF_INET; 
    serv_address.sin_port = htons(PORT); 

	inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr);

    connect(sock_c, (SOCKADDR *)&serv_address, sizeof(serv_address));

    while(1){
        printf(">>>");
        fgets(message, 100, stdin);
        write(sock_c, message, strlen(message));
        
        listen(sock_c, 1);
        read(sock_c, message2, sizeof(message2));
        printf("msg reçu du serv: %s\n", message2);

        memset(message2, 0, sizeof(message2));
        memset(message, 0, sizeof(message));

    }
}