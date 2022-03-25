#include <stdio.h>
#include <stdlib.h>
#include "rsa.h"
#include "proj.h"
#include <math.h>
#include <time.h>
#include <string.h>
#ifndef RSA_H
#define RSA_H


long extended_gcd(long a,long t,long *u, long *v){
    /* donnne la valeur des entier u et v par la methode de l'algorithme d'euclide etendu */
    if(a == 0){
        *u =0;
        *v =1;
        return t;
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t%a,a,&uPrim,&vPrim);
    *u = vPrim -(t/a)*uPrim;
    *v = uPrim;
    return uPrim;
}
uint16_t gcd(uint16_t a, uint32_t b){

	uint16_t temp;
	if (a > b)
	{
		temp = a;
		a = b;
		b = temp;
	}
	for (uint16_t i = a; i > 0; i--)
	{
		if (a % i == 0 && b % i == 0)
            return i;
	}
}
void generate_key_values(uint16_t e, uint16_t *p, uint16_t *q, uint32_t *n, uint32_t *phi){
    // generere la cle publique puis la cle privee
    do{
        *p = is_prime_naive(*p);
        do{
            *q=is_prime_naive(*q);
           
        }
        while(*p ==*q);
        *n = *p * *q;
        *phi = *n - *p - *q + 1;
    }
   while (gcd(e,*phi) != 1);

}
long* encrypt(char* chaine, long s, long n){
    long *t;
    int a;
    /* chiffre la chaine avec la cle publique ormis \0 */
    char c= chaine[0];
    while (c != '\0'){
        int a = (int)c;
        t[c] = modpow(n,s,n);
        c++;
    }
    return t;
    
}
char* decrypt(long* crypted, int size,long u, long n){
    char *messageDechifree;
    for(long i=0;i<size;i++){
        for(long i=0;i<size;i++){ // parcours du message chifree
            modpow(crypted[i],u,n);
        }
    }
    return messageDechifree;
}

int main(){
    printf("long = %ld octets\n",sizeof(long));
    printf("int = %lu octets\n",sizeof(int));
   
    return 0;
}



/*MES FONCTIONS DECRYPT ET ENCRYPT
	long* encrypt(char* chaine, long s, long n)
{
	long *tab=malloc(sizeof(long)*strlen(chaine));
    	if(!tab)
	{
      		fprintf(stderr,"erreur allocation\n");
      		return NULL;
    	}
    	
    	for (int i=0;i<strlen(chaine); i++){
	
      		tab[i]=modpow((long)chaine[i],s,n);
      		
      		
    	}
    	
	return tab;
} 

char* decrypt(long* crypted,int size, long u, long n)
{	
	char *res=malloc(sizeof(char)*(size+1));
	
  	for(int i=0;i<size;i++)
	{
    		res[i]=(char)modpow(crypted[i],u,n);
  	}
  	return res+'\0';
}
/*
#endif
