#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <ncurses.h>
#define PORT 8096


typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

int sock_c, valRead; 
char message[100];
SOCKADDR_IN serv_address;

void socketet(){
    sock_c = socket(AF_INET, SOCK_STREAM, 0); 

    serv_address.sin_family = AF_INET; 
    serv_address.sin_port = htons(PORT); 

    inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr);
    connect(sock_c, (SOCKADDR *)&serv_address, sizeof(serv_address));

}

int main(void) {
    socketet();
    WINDOW *w;
    char key = '+';
    initscr();
    do{
        clear();
        key = getch();
        switch(key){
            case 'o':
                wscanw(w, "%s", message);
                /* _rawmode = FALSE; */
                wprintw(w, "Name is %s\n", message);
                wrefresh(w);
                // printw(">>>");
                // fgets(message, 100, stdin);
                // wgetstr( message);
                // printw("You entered: %s", message);
                // printw("hello");
                // write(sock_c, message, strlen(message));
                // listen(sock_c, 1);
                // memset(message, 0, sizeof(message));
                break;
        }
    }
    while( !(key == 'e'));
        endwin();
        return 0;


    while(1){
            
        if(read(sock_c, message, sizeof(message))){
            printf("msg reçu du serv: %s\n", message);    
            listen(sock_c, 1);
            memset(message, 0, sizeof(message));
        }
    }
}
