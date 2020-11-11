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

//----------------------
// Exemple de fgets mais je pense ca marche que avec la lecture de fichier -- a voir
//----------------------
// #include <errno.h>
// #include <stdio.h>
// #include <stdlib.h>

// #define MAX_LENGTH 10

// int main( int argc, char * argv[] ) {
    
//     argc--;   argv++;
    
//     if ( argc == 0 ) {
//         printf( "Usage: sample filename\n" );
//         exit( 0 );
//     }
    
//     FILE * inputFile = fopen( argv[0], "r" );
//     if ( inputFile == NULL ) {
//         printf( "Cannot open file %s\n", argv[0] );
//         exit( -1 );
//     }
    
//     char * buffer = (char *) malloc( MAX_LENGTH );
//     while ( ! feof( inputFile ) ) {
//         fgets( buffer, MAX_LENGTH, inputFile );
//         if ( ferror( inputFile ) ) {
//             fprintf( stderr, "Reading error with code %d\n", errno );
//             break;
//         }
        
//         puts( buffer );        
//     }

//     free( buffer );
//     fclose( inputFile );
        
//     return 0;
// }