#include "part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    srand(time(NULL));
    long m = modpow(5,2,4);
    long b = modpow_naive(5,2,4);
    printf("%ld\n",random_prime_number(10,30,50));
    printf("%ld\n",random_prime_number(10,30,50));

    printf("%ld %ld",m,b);
    printf("============================================\n");
     long p=random_prime_number(3,5,50);
    long q=random_prime_number(3,5,50);

    long n,s,u;
    
    /* s pub u prive*/

    generate_key_values(p,q,&n,&s,&u);

    printf (" cle publique= (%lx,%lx ) \n",s,n);
  	printf (" cle privee= (%lx,%lx ) \n",u,n);


    char mess[10] ="sup";
  	int len=strlen(mess);
  	long *crypted = encrypt(mess, s, n);

  	printf("Initial message: %s \n",mess);
  	printf("Encoded representation : \n");
  	print_long_vector(crypted,len);

  	//dechiffrement
  	char* decoded=decrypt(crypted,len,u,n);
  	printf("Decoded:%s\n",decoded);
  
    return 0;
}