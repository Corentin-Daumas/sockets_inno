#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include "crypt.h"

int premierYN(int nbr);
int puissance(int nbr, int puiss);
int testEntree(int nbr);
void cleCryptagePublique();
void chiffrement(n);
void dechiffrage(n);
long int cd(long int a);



long int r, msg_encr[100], msg_code[100], msg_decode[100];
int test=0, e[100], d[100], f, p, q; 
char msg[100];


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
	
	cleCryptagePublique();

	/*recuperation du message clavier*/
	printf("Entrer votre message :");
	scanf("%s",msg);
	for(int i = 0; msg[i] != '\0'; i++){
    	msg_encr[i] = msg[i]; 
	}
	for(int i = 0; msg[i] != '\0'; i++){ //test print du char en long int
		printf("%d\n",msg_encr[i]);
	}
	chiffrement(n);
	printf("---fin---\n");
	dechiffrage(n);
	printf("---fin---\n");


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

// int puissance(long long int nbr, long long int puiss){
// 	int calcule = nbr;
// 	for(int i = 1; i<puiss; i++){
// 		printf("%d\n", calcule);
// 		calcule = calcule*nbr;
// 	}
// 	return calcule;
// }

/* VERSION 1 DE LA CLE D ENCRYPTION*/
// void cleCryptagePublique(){
// 	int compt = 0;
// 	for(int i = 2; i < f; i++){
// 		test = premierYN(i);
		
// 		if(test == 1 && i != p && i != q){
// 			e[compt] = i;
// 			int a = cd(e[compt]);
// 			if (a > 0){
// 				d[compt] = a;
// 				compt++;

// 			}
// 			if (compt == 99){
// 				break;
// 			}
// 		}

// 		printf("e=%ld    d=%ld\n",e[compt] ,d[compt]);
// 	}	
// }


void cleCryptagePublique()
{
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

long int cd(long int a)
{
  long int k = 1;
  while(1)
  {
    k = k + f;
    if(k % a == 0)
     return(k / a);
  }
}


void chiffrement(n){
	printf("debut chiffrement\n");
	// for (int i = 0; i < strlen(msg); ++i){
	for(int i = 0; msg[i] != '\0'; i++){
		long long int a = msg_encr[i]-96;
		a = pow(a, e[0]);
		// a = puissance(a, e[0]);	
		printf("puissance>>>%lld\n", a);
		a = a % n; // -96 parce que ASCII
		printf("modulo>>>%lld\n", a);
		msg_code[i]= a+96; // +96 parce que ASCII
		printf("----%lld\n", msg_code[i]);
	}
	// printf("%ld\n", msg_code);
	
}

void dechiffrage(n){
	printf("debut dechiffrement\n");
	for(int i = 0; msg[i] != '\0'; i++){
		long long int a = msg_code[i]-96;
		printf("a+96:%lld   -   %d\n", a+96, d[0]);
		a = pow(a, d[0]);
		printf("puissance:%lld\n", a);
		a = a % n;
		printf("modulo+96:%lld\n", a+96);
		printf(">>>%lld\n", a);
		msg_decode[i]= a+96;
		printf("%d\n", msg_decode[i]);
	}
	
}



