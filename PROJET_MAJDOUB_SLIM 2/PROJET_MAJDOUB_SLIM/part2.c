#include"part2.h"


long extended_gcd(long s,long t,long *u, long *v){
    /* donnne la valeur des entier u et v par la methode de l'algorithme d'euclide etendu */
    if(s == 0){
        *u =0;
        *v =1;
        return t;
    }// cas de base

    long uPrim, vPrim;
    long gcd = extended_gcd(t%s,s,&uPrim,&vPrim);
    *u = vPrim -(t/s)*uPrim;
    *v = uPrim;
    return gcd;
}

void generate_key_values(long p,long q,long* n,long *s,long* u){
    /* genere la cle publique puis la cle privee a partir des nombres premiers p et q en suivant le protocole RSA */

    *n = p*q;
    long t = (p-1)*(q-1);
    *s = rand_long(2,t);
    long v;
    while (extended_gcd(*s,t,u,&v)!=1){
        *s = rand_long(2,t);
    }
    
}
// alloc dynamique
long* encrypt(char* chaine, long s, long n)
{
    /* chiffre une chaine de caractere a l'aide de la cle publique 
        */
	long *tab=malloc(sizeof(long)*strlen(chaine));
    int i = 0;
    	while(chaine[i]!='\0'){
            int c = (int)chaine[i]; // on caste le caractere c en entier
            long val = (long)c;
            tab[i]=modpow(val,s,n);
            i++;
        }
    return tab;

} 
// alloc dynamique
char* decrypt(long* crypted,int size, long u, long n)
{	
    /* dechiffre un message a l'aide de la cle secrete */
	char *res=malloc(sizeof(char)*(size+1));
    int i;
    if (res == NULL) return NULL;
    else{
  	    for(int i=0;i<size;i++)
	    {
    	    res[i]=(char)modpow(crypted[i],u,n);
  	    }

    }
      res[size]='\0';
      return res;
}
void print_long_vector(long *result , int size ){ 
	printf ("Vector: [ "); 
  	for(int i =0; i < size ; i ++)
	{
    		printf("%lx \t", result[i]);
  	} 
  	printf ("] \n");
}

