/*#include <stdio.h>
#include <stdlib.h>

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
            
            //fprintf(fichier,"%.2lf  %ld\n",tps,modpow_naive(a,m,n)); // fichier modpow_naive
            fprintf(f,"%.2lf    %ld\n",tps,m);
            a*=1;
            m+=1;
            
            tps = tps + 0.7;
        }
   
    fclose(fichier);
    fclose(f);
    }
    return 0;
}
*/
