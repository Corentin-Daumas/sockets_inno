#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <poll.h>
#include <math.h>
#include <gmp.h>
#include <assert.h>

#define PORT 8096

int premierYN(int nbr);
int testEntree(int nbr);
void cleCryptagePublique();
void chiffrement(n);
void dechiffrage(n);
long int cd(long int a);
int computePowm(input_nbr, input_exp, input_mod);


typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

long int r, msg_encr[100], msg_code[100], msg_decode[100], codeRecu[100];
int test=0, e[100], d[100], f, p, q, sock_c, valRead; 
char message[100], codeEnvoie[100];

SOCKADDR_IN serv_address;
    
int main(int argc, char const *argv[]) {


    int n;
    /*récupéraction de n et p*/
    printf("entrer p : ");
    scanf("%d", &p);
    p = testEntree(p);

    printf("entrer q : ");
    scanf("%d", &q);
    q = testEntree(q);

    printf("p = %d, q = %d\n", p, q);

    /*déclaration des paramètres*/
    n = p*q;
    f = (p-1)*(q-1);

    viderBuffer();

    cleCryptagePublique();
    printf("------------------------\n");


    sock_c = socket(AF_INET, SOCK_STREAM, 0); 

    serv_address.sin_family = AF_INET; 
    serv_address.sin_port = htons(PORT); 

	inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr);
    connect(sock_c, (SOCKADDR *)&serv_address, sizeof(serv_address));


    while(1){
        // on vide toutes les mémoires des tableaux pour ne pas avoir de charactères indésirables
        for(int i = 0; i<100; i++){
            message[i] = 0;
            msg_code[i] = 0;
            msg_encr[i] = 0;
            codeEnvoie[i] = 0;
        }
        printf("\n");
        if(fgets(message, 100, stdin)){ // dans l'idéal le rendre non bloquant avec select() ou poll() par exemple
            
            message[strlen(message)-1] = 0;
            for(int i = 0; message[i] != '\0'; i++){ // avant d'écrire dans la socket il faut chiffrer le message
                msg_encr[i] = message[i]; 
                // printf("%d ", msg_encr[i]);
            }
            // for(int i = 0; message[i] != '\0'; i++){ // test print du char en long int
            //     printf("%d\n",msg_encr[i]);
            // }
            chiffrement(n);
            // for(int i=0; sizeof(msg_code); i++){
            //     printf("%d\n", msg_code[i]);
            // } 
            // printf("\nmessage envoyé:  %s\n", codeEnvoie);
            write(sock_c, codeEnvoie, sizeof(codeEnvoie)); // on écrit/envoie le message chiffré dans la socket
            listen(sock_c, 1); // on remet la socket en écoute pour receptionner le prochain message
            memset(message, 0, sizeof(message)); // on nettoie la mémoire de message pour pas surcharger le prog
        }

        if(read(sock_c, message, sizeof(message))){
            // printf("%s\n", message);
            dechiffrage(n);
            // printf("messsage reçu:");
            // for(int i = 0; message[i] != '\0'; i++){
                // printf("%c\n", msg_decode[i]);    
            // }
            listen(sock_c, 1);
            memset(message, 0, sizeof(message));
        }

        }
    }
void viderBuffer(void){
  int c;
  while((c=getchar()) != EOF && c != '\n');
 
}

int testEntree(int nbr){
    while(test == 0){
        test = premierYN(nbr);  
        if(test == 0){
            printf("ce n'est pas un nombre premier\n");
            scanf("%d", &nbr);
        }   
        else{
            printf("c'est un nombre premier\n");
            test = 0;
            return nbr;
        }
    }
}

int premierYN(int nbr){
    if(nbr == 1){
        return 0;
    }
    else{
        int i;
        r = sqrt(nbr);
        for(i = 2; i <= r; i++){
            if(nbr % i == 0){
                return 0;
            }
        }
        return 1;
    }
}

int computePowm(input_nbr, input_exp, input_mod){
    mpz_t nbr; mpz_init(nbr); mpz_set_ui(nbr, input_nbr);
    mpz_t exp; mpz_init(exp); mpz_set_ui(exp, input_exp);
    mpz_t mod; mpz_init(mod); mpz_set_ui(mod, input_mod);

    mpz_powm(nbr, nbr, exp, mod);
    
    // printf (" resultat chiffrement = ");
    // mpz_out_str(stdout,10,nbr);
    // printf ("\n");
    int res = mpz_get_ui(nbr);

    mpz_clear(nbr);

    return res;
}

void cleCryptagePublique(){
  int k;
  k = 0;
  for(int i = 2; i < f; i++)
  {
    if(f % i == 0)
     continue;
    int flag = premierYN(i);
    if(flag == 1 && i != p && i != q)
    {
     e[k] = i;
     flag = cd(e[k]);
    if(flag > 0)
    {
     d[k] = flag;
     printf("e=%ld    d=%ld\n",e[k] ,d[k]);
     k++;
    }
   if(k == 99)
    break;
   }
 }
}

long int cd(long int a){
  long int k = 1;
  while(1)
  {
    k = k + f;
    if(k % a == 0)
     return(k / a);
  }
}

void chiffrement(n){
    // printf("debut chiffrement\n");
    // for (int i = 0; i < strlen(msg); ++i){
    for(int i = 0; message[i] != '\0'; i++){
        int a = msg_encr[i]-96;
        a = computePowm(a, e[0], n);
        msg_code[i] = a; // +96 parce que ASCII
        // printf("chiffré +96 :%d\n", msg_code[i]);
    }
    for(int i = 0; message[i] != '\0'; i++){
        codeEnvoie[i] = (char) msg_code[i];
        // printf("%d ", msg_code[i]);
    }
    // printf("----------%s\n", test2);
}

void dechiffrage(n){
    // printf("debut dechiffrement\n");
    // memset(msg_code, 0, sizeof(msg_code));
    for(int i = 0; message[i] != '\0'; i++){
        codeRecu[i] = message[i];
        // printf("%d ", codeRecu[i]);
    }
    printf("\nmessage reçu:  ");
    for(int i = 0; message[i] != '\0'; i++){
        // printf(">>>%d\n", codeRecu[i]);
        int a = codeRecu[i];
        a = computePowm(a, d[0], n);
        msg_decode[i]= a+96;
        printf("%c", msg_decode[i]);
    }
    printf("\n");
    // printf("%d\n", strlen(msg_decode));
}


