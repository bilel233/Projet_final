#include"rsa.h"
#define DESTINATION 60



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

void generate_key_values(long p,long q,long* n,long *s,long* u){
    /* genere la cle publique puis la cle privee a partir des nombres premiers p et q en suivant le protocole RSA */

    *n = p*q;
    long t = (p-1)*(q-1);
    *s = rand_long(2,t);
    long v;
    while (extended_gcd(*s,t,u,&v)!=1){
        *s = rand_long(2,t);
    }
    return;
}
// alloc dynamique
long* encrypt(char* chaine, long s, long n)
{
    /* chiffre une chaine de caractere a l'aide de la cle publique 
        */
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
// alloc dynamique
char* decrypt(long* crypted,int size, long u, long n)
{	
    /* dechiffre un message a l'aid ede la cle secrete */
	char *res=malloc(sizeof(char)*(size+1));
    char *dest = (char*)malloc(sizeof(char)*DESTINATION);
    if (res == NULL && dest == NULL) return NULL;
    else{
  	    for(int i=0;i<size;i++)
	    {
    	    res[i]=(char)modpow(crypted[i],u,n);
  	    }
    }
      strcat(dest,res);
    return dest;   
}

int main(){
    printf("long = %ld octets\n",sizeof(long));
    printf("int = %lu octets\n",sizeof(int));
   
    return 0;
}

