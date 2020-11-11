#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int main(int argc, char const *argv[]) {
    char message[1024];

    scanf("%[^\n]", message);
    printf("%s\n", message);

    memset (message, 0, sizeof (message)); /* remise a zero */
    printf("%s>>\n", message); /* print char vide */

    return 0;
}

