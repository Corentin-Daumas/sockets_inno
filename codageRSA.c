#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int premierYN(int nbr);
int testEntree(int nbr);

long int r;
int test=0;

int main(int argc, char const *argv[]) {
	int p, q, n, f, d, e;

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

