#include <stdio.h>

int main(int argc, char const *argv[]){
   int i, x;                  // on declare 2 integers
   char str[100];             // on declare un tableau 

   printf("\nEntrez votre message :\t");
   gets(str);                 //fonction gets similaire à scanf() mais d'utiliser des espaces ATTENTION msg d'erreurs à corriger 

   printf("\nChoisir une option :\n");
   printf("1 = Encrypter votre message.\n");
   printf("2 = Decrypter votre message.\n");
   scanf("%d", &x);             

   //switch permet de faire un menu
   switch(x){
    // les case sont les différents choix du menu
   case 1:
      for(i = 0; (i < 100 && str[i] != '\0'); i++)
        str[i] = str[i] + 3; //la clé d'encryption est 3  on l ajoute à la valeur ASCII

      printf("\nMessage encrypté: %s\n", str);
      break;

   case 2:
      for(i = 0; (i < 100 && str[i] != '\0'); i++)
        str[i] = str[i] - 3; //la clé d'encryption est 3  on l'enleve à la valeur ASCII

      printf("\nmessage decrypté: %s\n", str);
      break;

   default:       // si nombre choisi != de 1 ou 2
      printf("\nErreur\n");
   }
   return 0;
}