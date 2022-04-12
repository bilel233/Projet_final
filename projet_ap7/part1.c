#include "part1.h"
#define MAX_LENGTH 25
#define TAILLE_FICHIER 200


clock_t  temps_initial;
clock_t  temps_final;
double temps_cpu1;

int is_prime_naive(long p){
    /*renvoie 1 si p est premier, O sinon. 
        */
    for(int i=3 ;i<p;i++){
        if (p%i==0){
            return 0;
        }

    }
    return 1;
}

long plus_grand(){
    /*renvoie le plus grand nombre premier capable de tester en moins de 2 milliemes de secondes 
        */
    long p=3;
    while(temps_cpu1<0.002 ||is_prime_naive(p)==0){
        
        temps_initial=clock();
        is_prime_naive(p);
        temps_final=clock();
        temps_cpu1=(( double)(temps_final  - temps_initial))/CLOCKS_PER_SEC;
        p+=2;
    }
    return p;
}


long modpow_naive(long a, long m, long n){
    /*prend en entree trois entree a,m et n et renvoie la valeur de a mod n ; en evitant de calculer a^m, par methode naïve */
        
    long c = 1;
    long res = a;
    for(long i=1;i<=m;i++){
        res = c;
        c = c * a;
        res = res % n;
    }
    return res;

}    



long modpow(long a,long m,long n)
{
	if(m==1)
	{
		return a%n;
	}

	if( m % 2 == 0)
	{
		long b= modpow(a, m/2, n);
		return b* b % n;
	}
	else
	{
		long b=modpow(a,floor(m/2),n);
		return a * b * b % n;
	}
}


int witness(long a, long b,long d,long p){
    /* renvoie 1 si a est un temoin de Miller ; O sinon
        */
    long x = modpow(a,d,p);
    if(x==1){
        return 0;
    }
    for(long i=0; i < b; i++){
        if(x ==p-1){
            return 0;
        }
        x = modpow(x,2,p);
    }
    return 1;
}
long rand_long(long low,long up){ 
    /* renvoie un entier generes aleatoirement entre low et up
        */

    long val =  rand() % (up-low+1)+low;
    return val;
}
long power(long a,long b){
    long cpt=1;
    for(int i = 0;i<=b;i++){
        cpt*=a;
        
    }
    return cpt;
}
int is_prime_miller(long p, int k){
    /* realise le test de miller-Rabin */
    if (p == 2){
        return 1;
    }
    if(!(p & 1) || p <= 1){
        return 0;

    }
    // on determine b et d
    long b = 0;
    long d = p-1;
    while(!(d & 1)){//tant que d n’est pas impair
    d = d / 2;
    b+=1;
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;
    for(i=0;i<k;i++){
        a = rand_long(2, p-1);
        if(witness(a,b,d,p)){
            return 0;
        }
    }
    return 1;
}
    
long random_prime_number(int low_size, int up_size, int k)
{  
	long p=rand_long(pow(2,low_size-1),pow(2,up_size)-1);

	while(is_prime_miller(p,k)==0)
	{
		p=rand_long(pow(2,low_size-1),pow(2,up_size)-1);
  	}
  	return p;
}

long randomprime(int low_size,int up_size,int k){
    int trouver =0;
    int p;
    long min=pow(2,low_size-1);
    long max=pow(2,up_size)-1;
    while(trouver==0){
        p=rand_long(min,max);
        if (is_prime_miller(p,k)==1){
            trouver=1;
        }
    }
    return p;
}