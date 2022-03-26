#include "proj.h"
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


long modpow(long a, long m, long n){
    /* realise l'exponentielle modulo n de maniere recursive
        */
    if ( m== 0) return 0;
    
    else if (m % 2 ==0) {
        long b = modpow(a,m/2,n);
        return b*b%n;
    }
    else{
        long b = modpow(a,m-1,n);
        return b*a%n;
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

    return rand() % (up - low +1)+low;
}
int is_prime_miller(long p, int k) { 
    /* renvoie 0 si un temoin de Miller est trouve. 1 sinon
        */
    if (p == 2) {
        return 1; 
    }
    if (!(p & 1) || p <= 1) { //on verifie que p est impair et different de 1 return 0;
        return 0;
    }
        //on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!(d & 1)){ //tant que d n’est pas impair
        d = d/2;
        b=b+1; 
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;
    for(i = 0;i<k;i++){
        a = rand_long(2, p-1);
        if(witness(a,b,d,p)){ 
            return 0;
       }
    }
return 1; 
}


long random_prime_number(int lowsize, int upsize, int k){
    int v;
    //retourne un nombre premier de taille comprise entre low size et up size
    for(long i = 8;i<= 15;i++){
        long val = rand_long(lowsize,upsize);
        v=is_prime_miller(val,k);
    }
   
return v == 1;
}



int main(){
    return 0;
}