#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int premierYN(int nbr);
int testEntree(int nbr);
void cleCryptagePublique();
void chiffrement(msg,n);
long int cd(long int a);



long int r;
int test=0, e[100], d[100], f, p, q;


int main(int argc, char const *argv[]) {
	
	int n;
	char msg;

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
	printf("%s",msg);
	//chiffrement(msg,n);
	printf("fin");


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

void chiffrement(msg,n){
	printf("debut chiffrement");

	char msgcode[100];
	for (int i = 0; i < strlen(msg); ++i){
		printf("for");
		msgcode[i]= (i**e) % n;
	}
	printf("%s", msgcode);
	
}