#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int main(int argc, char const *argv[]) {
    char message[1024];
    scanf("%24[^\n]", message);
    printf("%s\n", message);
    // int i = 0;
    memset (message, 0, sizeof (message));
        // while(i!=5){
        //     printf("%s\n", message);
        //     message[i] = '\0';
        //     i++;
        // }
    printf("%s>>\n", message);
    return 0;
}

