#include <stdio.h>
#include <sys/socket.h> 
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

struct sockaddr_in serv; 
int socket_s; 
int conn;
char message[100], buffer[100];  

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int main(int argc, char const *argv[]) { 
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8096);
	serv.sin_addr.s_addr = INADDR_ANY;
	socket_s = socket(AF_INET, SOCK_STREAM, 0); 

	bind(socket_s, (struct sockaddr *)&serv, sizeof(serv)); 
	listen(socket_s,5); 
	

	while(conn = accept(socket_s, (struct sockaddr *)NULL, NULL)) {
	    int enfant;
	    enfant = fork();
	    if(enfant == 0) {
	        while (recv(conn, message, 100, 0)>0) {
	        	// read(conn, message, sizeof(message));
	            printf("%d: %s\n", conn, message);

				write(conn,message,sizeof(message));
				listen(conn,1);
				// read(conn,str,sizeof(str));

				// memset (buffer, 0, sizeof (buffer));
	            memset (message, 0, sizeof (message));
	        }
	        exit(0);
	    }
	}
}




// #include<sys/socket.h>
// #include<sys/types.h>
// #include<stdio.h>
// #include<arpa/inet.h>
// #include<netinet/in.h>
// #include<string.h>
// #include<unistd.h>
// #define SER_PORT 8096
// int main()
// {
// int a,sersock,newsock,n;
// char str[25],str2[25];
// struct sockaddr_in seraddr;
// struct sockaddr_in cliinfo;
// socklen_t csize=sizeof(cliinfo);
// seraddr.sin_family=AF_INET;
// seraddr.sin_port=htons(SER_PORT);
// seraddr.sin_addr.s_addr=htonl(INADDR_ANY);

// sersock=socket(AF_INET,SOCK_STREAM,0);
// bind(sersock,(struct sockaddr *)&seraddr,sizeof(seraddr));
// listen(sersock,1);

// newsock=accept(sersock,(struct sockaddr *)&cliinfo,&csize);
// read(newsock,str,sizeof(str));
// printf("\n client msg:%s",str);
// printf("\n server msg:");
// scanf("%s",str2);
// write(newsock,str2,sizeof(str2));
// listen(newsock,1);
// read(newsock,str,sizeof(str));
// n=strcmp(str,"BYE");
// a=strcmp(str2,"BYE");
// while(n!=0||a!=0);
// close(newsock);
// close(sersock);
// return 0;
// }
 

