#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

struct sockaddr_in serv; 
int socket_c;
int conn; 
char message[100], buffer[100]; 

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int main(int argc, char const *argv[]) { 
	socket_c = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8096);
	inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr); 
	connect(socket_c, (struct sockaddr *)&serv, sizeof(serv)); 

	while(1) {
	    printf(">>> ");
	    fgets(message, 100, stdin);
	    send(socket_c, message, strlen(message), 0);

	    listen(socket_c, 1);
	    read(socket_c, buffer, sizeof(buffer));
	    printf("\nserver msg:%s",buffer);

	    memset (buffer, 0, sizeof(buffer));
	    memset (message, 0, sizeof(message));

	}
}




// #include<stdio.h>
// #include<sys/socket.h>
// #include<sys/types.h>
// #include<arpa/inet.h>
// #include<netinet/in.h>
// #include<unistd.h>
// #define SER_PORT 8096

// int main(int count,char*arg[])
// {
// int a,clisock;
// char str[20],str2[20];
// struct sockaddr_in cliaddr;
// cliaddr.sin_port=htons(SER_PORT);
// cliaddr.sin_family=AF_INET;
// cliaddr.sin_addr.s_addr=inet_addr(arg[1]);
// clisock=socket(AF_INET,SOCK_STREAM,0);

// connect(clisock,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
// scanf("%s",&str);
// write(clisock,str,sizeof(str));
// listen(clisock,1);
// read(clisock,str2,sizeof(str2));
// printf("\nserver msg:%s",str2);
// printf("\nclient msg:");
// scanf("%s",&str);
// a=strcmp(str2,"BYE");
// write(clisock,str2,sizeof(str2));
// while(a!=0);
// close(clisock);
// return 0;
// }
//  