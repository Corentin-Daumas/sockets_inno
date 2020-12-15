#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// #include<string.assert.h>
#include <gmp.h>
#include <assert.h>

int premierYN(int nbr);
int puissance(int nbr, int puiss);
int testEntree(int nbr);
void cleCryptagePublique();
void chiffrement(n);
void dechiffrage(n);
long int cd(long int a);
int computePowm(input_nbr, input_exp, input_mod);


long int r, msg_encr[100], msg_code[100], msg_decode[100];
int test=0, e[100], d[100], f, p, q; 
char msg[100];


int main(int argc, char const *argv[]) {

	// int test = computePowm(171, 37, 77);
	// printf(">>>%d\n", test);

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

int computePowm(input_nbr, input_exp, input_mod){
	mpz_t nbr; mpz_init(nbr); mpz_set_ui(nbr, input_nbr);
	mpz_t exp; mpz_init(exp); mpz_set_ui(exp, input_exp);
	mpz_t mod; mpz_init(mod); mpz_set_ui(mod, input_mod);

	mpz_powm(nbr, nbr, exp, mod);
	
	printf (" resultat chiffrement = ");
	mpz_out_str(stdout,10,nbr);
	printf ("\n");
	int res = mpz_get_ui(nbr);

	mpz_clear(nbr);

	return res;




  // char inputStr[1024];

  // mpz_t n;
  // int flag;

  // printf ("Enter your number: ");
  // scanf("%1023s" , inputStr);

  // mpz_init(n);
  // mpz_set_ui(n,0);

  // flag = mpz_set_str(n,inputStr, 10);
  // assert (flag == 0);

  // mpz_pow_ui(n,n,37);
  // printf (" nbr^37 = ");
  // mpz_out_str(stdout,10,n);
  // printf ("\n");
  // return n;
  // mpz_clear(n);
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
	printf("debut chiffrement\n");
	// for (int i = 0; i < strlen(msg); ++i){
	for(int i = 0; msg[i] != '\0'; i++){
		int a = msg_encr[i]-96;
		a = computePowm(a, e[0], n);
		msg_code[i]= a+96; // +96 parce que ASCII
		printf("chiffré +96 :%c\n", msg_code[i]);
	}
}

void dechiffrage(n){
	printf("debut dechiffrement\n");
	for(int i = 0; msg[i] != '\0'; i++){
		int a = msg_code[i]-96;
		a = computePowm(a, d[0], n);
		msg_decode[i]= a+96;
		printf("dechiffré +96 :%c\n", msg_decode[i]);
	}
}



