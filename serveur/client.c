#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <poll.h>
#include <math.h>
#include <gmp.h>
#include <assert.h>

#define PORT 8080

int premierYN(int nbr);
int testEntree(int nbr);
void cleCryptagePublique();
void chiffrement(int n);
void dechiffrage(int n);
long int getD(long int a);
int computePowm(int input_nbr, int input_exp, int input_mod);
void viderBuffer(void);

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

long int r, msg_encr[100], msg_code[100], msg_decode[100], codeRecu[100];
int test=0, e[100], d[100], f, p, q, sock_c, valRead; 
char message[100], codeEnvoie[100];

SOCKADDR_IN serv_address;
    
int main(int argc, char const *argv[]) {


    /*récupéraction de n et p*/
    int n;
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

    /* déclaration de la socket client */
    sock_c = socket(AF_INET, SOCK_STREAM, 0); 

    serv_address.sin_family = AF_INET; 
    serv_address.sin_port = htons(PORT); 

	// inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr); //pas utile ici
    connect(sock_c, (SOCKADDR *)&serv_address, sizeof(serv_address));


    while(1){
        // on vide toutes les mémoires des tableaux pour ne pas avoir de caractères indésirables
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
            }

            chiffrement(n);

            write(sock_c, codeEnvoie, sizeof(codeEnvoie)); // on écrit/envoie le message chiffré dans la socket
            listen(sock_c, 1); // on remet la socket en écoute pour receptionner le prochain message
            memset(message, 0, sizeof(message)); // on nettoie la mémoire de message pour pas surcharger le prog
        }

        if(read(sock_c, message, sizeof(message))){ // lis la socket et place le contenant dans "message"
            dechiffrage(n);
            listen(sock_c, 1);
            memset(message, 0, sizeof(message));
        }
        }
    }
void viderBuffer(void){
    int c;
    while((c=getchar()) != EOF && c != '\n');
}

/* On verifie que les entrées p et q sont des nombres premiers */
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

/* Test si un nombre est premier ou non */
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

/* Fonction qui s'occupe de l'exposant et du modulo pour chiffrer les caractères */
int computePowm(int input_nbr, int input_exp, int input_mod){
    mpz_t nbr; mpz_init(nbr); mpz_set_ui(nbr, input_nbr);
    mpz_t exp; mpz_init(exp); mpz_set_ui(exp, input_exp);
    mpz_t mod; mpz_init(mod); mpz_set_ui(mod, input_mod);
    mpz_powm(nbr, nbr, exp, mod);

    int res = mpz_get_ui(nbr);

    mpz_clear(nbr);
    return res;
}

/* Fonction qui définie les multiples paires possibles de e et d */
void cleCryptagePublique(){
    int k;
    k = 0;
    for(int i = 2; i < f; i++){
        if(f % i == 0){
            continue;
        }
        int flag = premierYN(i);
        if(flag == 1 && i != p && i != q){
            e[k] = i;
            flag = getD(e[k]);
            if(flag > 0){
                d[k] = flag;
                printf("e=%ld    d=%ld\n",e[k] ,d[k]);
                k++;
            }
            if(k == 99){
                break;
            }
        }
    }
}

/* Fonction qui retourne les valeurs de d en fonction des valeurs de e */
long int getD(long int a){
    long int k = 1;
    while(1){
        k = k + f;
        if(k % a == 0){
            return(k / a);
        }
    }
}

/* Fonction qui s'occupe de chiffrer caractères par caractères */
void chiffrement(int n){
    // printf("debut chiffrement\n");
    for(int i = 0; message[i] != '\0'; i++){
        int a = msg_encr[i]-96;
        a = computePowm(a, e[0], n);
        msg_code[i] = a; // +96 parce que ASCII
    }
    for(int i = 0; message[i] != '\0'; i++){
        codeEnvoie[i] = (char) msg_code[i];
        // printf("%d ", msg_code[i]);
    }
    // printf("----------%s\n", test2);
}

/* Fontion qui déchiffre le message reçu */
void dechiffrage(int n){
    // printf("debut dechiffrement\n");
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
        if(msg_decode[i] == '}'){
            printf(" ");
        }
        else{
            printf("%c", msg_decode[i]);
        }
    }
    printf("\n");
    // printf("%d\n", strlen(msg_decode));
}

