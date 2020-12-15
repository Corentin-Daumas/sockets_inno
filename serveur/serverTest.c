 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>


static void   sigchld_handler(int signo) {  
    pid_t PID;   
    int status;  

  do {  
     PID = waitpid(-1,&status,WNOHANG);  
      }   
  while ( PID != -1 );  
// Re-instate handler

  signal(SIGCHLD,sigchld_handler);  
}

  int main(int argc ,char *argv[])
{ 
   int server_socket; 
    int client_socket , size_structure,read_size,binds;
    int *new_socket;
    struct sockaddr_in server, client ;
    server_socket = socket(AF_INET, SOCK_STREAM,0);
    char client_message[100]="";
     pid_t PID;                    /* Process ID */  
/* * Set signal handler for SIGCHLD: */
signal(SIGCHLD,sigchld_handler);

    if(server_socket == -1)
    {  
        puts("socket has nt been created");
    }
    else 
        puts("socket has been created");

    //give values to the structure for server
 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

//step 3 bind karo 
binds = bind(server_socket,(struct sockaddr*)&server,sizeof(server));

if(binds<0)
    {
    perror("bind failed.Error");
    return 1;
    } 
    puts("SOcket has been binded to address");

//listen to incoming request

listen(server_socket,30); 
size_structure = sizeof(struct sockaddr_in);
FILE *fp;
fp =fopen("test.txt","w");

while (1)
    {
    	client_socket = accept(server_socket,(struct sockaddr *)&client,(socklen_t*)&size_structure);
     if(client_socket<0)
        { 
            puts("client is nt connected");
        return 1;
        }
    else 
        puts("connection accepted");

    if((PID = fork())== -1)
        { 
            close(client_socket);
            continue;
        }

    else if(PID >0)
        {
        close(client_socket);
        continue;
        }

    setlinebuf(fp);

    while(( read_size=recv(client_socket,client_message,2000,0))>0)
        {

        puts(client_message);
            write(client_socket,client_message,sizeof(client_message));
        for(int i=0;i<500;i++)
            { 
            fwrite(client_message,1,sizeof(client_message),fp);
            } 
        if(PID==-1)
            {  
            exit(0);
            }
        memset(client_message,0,strlen(client_message));

        }

    if(read_size==-1)
        {
        puts("client disconnected");
        fflush(stdout);
        close(client_socket);
        exit(0);
        }
    else if(read_size == 0)
        { 
            printf("recveiving failed");
            }
    }



memset(client_message,0,strlen(client_message));
close(client_socket);
fclose(fp);
return 0;
}