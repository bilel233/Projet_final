#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>
#ifndef PROJ_H
#define PROJ_H
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

//int testPrimaliteMillerRabin(int p,int d,int s,int n){
    /* effectue le test de primalite sur notre entier impair p */
  //  int N = modpow(2,s,n)*d+1; //ecriture de N avec d impair
    //long val = rand_long(1,p-1); 
    // calcul de a^d mod n
    //if (modpow(val,d,N) == 1 || modpow(val,d,N) == -1){
      //  return 0; // temoin de miller trouve
    //}
    //for(int i = 1;i<=s;i++){
      //  int deux = modpow(2,i,N);
        //int a = modpow(val,d*deux,N);
        ///if (witness(a,deux,d,p) == -1){
           // return 0;
        //}            // on ne peut rien dire ; on s'arrete
        //else if (witness(a,deux,d,p) == 1){
         //   return 0; // p est compose ; on s'arrete.

        //}

        
        
    //}
    // Si on arrive a la fin de la boucle et que a^d^2s !=1 mod n, on conclut
    // que p est compose.

    //return 0;
//}
long random_prime_number(int lowsize, int upsize, int k){
    int v;
    //retourne un nombre premier de taille comprise entre low size et up size
    for(long i = 8;i<= 15;i++){
        long val = rand_long(lowsize,upsize);
        v=is_prime_miller(val,k);
    }
   
return v == 1;
}



int main(int argc,char* argv[]){
    printf("test de la fonction is_prime_naive()\n");
    printf("%d\n",is_prime_naive(15));
    printf("%d\n",is_prime_naive(21));
    printf("%d\n",is_prime_naive(11));
    printf("test de \'is_prime_naive()\' par la fonction assert\n'");
    assert(is_prime_naive(33)==0);
    assert(is_prime_naive(7)==1);
    assert(is_prime_naive(50)==0);
    printf("----------------------------------------------------------------\n");
    printf("test de la fonction modpow_naive\n");
    printf("%ld\n",modpow_naive(2,3,2));
    printf("%ld\n",modpow_naive(2,4,5));
    printf("%ld\n",modpow_naive(5,3,7));
    printf("test de \'is_prime_naive()\' par la fonction assert\n'");
    assert(modpow_naive(7,2,7)==0);
    assert(modpow_naive(8,3,2)==0);
    assert(modpow_naive(2,9,2)==0);
    printf("----------------------------------------------------------------\n");
    //printf("%ld\n",plus_grand());
    printf("test de la fonction modpow\n");
    printf("%ld\n",modpow(2,3,2));
    printf("%ld\n",modpow(3,2,5));
    printf("%ld\n",modpow(5,5,5));
    printf("test de la fonction \'modpow\' par ajout de la fonction assert\n");
    assert(modpow(2,3,2)==0);
    assert(modpow(3,2,5)==0);
    assert(modpow(5,5,5)==0);
    printf("----------------------------------------------------------------\n");

    FILE *fichier;
    FILE *f; // fonction modpow
    long m;
    float tps = 0.;
    fichier = fopen("moppow_naive.txt","w");
    f = fopen("modpow.txt","w");
    if (fichier != NULL){
        for(int i=0;i<TAILLE_FICHIER;i++){
            a = 5;
            m = 2;
            n = 2;
            //fprintf(fichier,"%.2lf  %ld\n",tps,modpow_naive(a,m,n)); // fichier modpow_naive
            fprintf(f,"%.2lf    %ld\n",tps,m);
            a*=1;
            m+=1;
            n*=4;
            tps = tps + 0.7;
        }
   
    fclose(fichier);
    fclose(f);
    }
    return 0;
}
#endif