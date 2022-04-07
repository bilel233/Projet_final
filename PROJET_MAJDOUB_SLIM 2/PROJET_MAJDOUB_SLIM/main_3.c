#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part3.h"
#include "part2.h"

void generate_random_data(int nv,int nc){
    /* genere des couples de cles puis realisela creation de fichiers */

    if(nc>nv){
        printf("fonction generate_random_data: Erreur nc ne doit pas etre inferieur a nv\n");
        return;
        FILE *f1;
        FILE *f2;
        FILE *f3;
        f1 = fopen("keys.txt","w");
        f2 = fopen("candidates.txt","w");
        f1 = fopen("declarations.txt","w");

        if (f1 == NULL || f2 == NULL || f3 == NULL){
            printf("geneate random data : e'rreur d'ouverture \n");
            return;
        }
        KEY* pkey = (KEY*)malloc(sizeof(KEY));
        KEY* skey = (KEY*)malloc(sizeof(KEY));

        char** tabClesElecteurs = (char**)malloc(sizeof(char*)*nv);
        if (tabClesElecteurs == NULL) return;
        for(int i=0;i<nv;i++){
            tabClesElecteurs[i] = NULL;

        }
        char** tabSkeyElecteurs = (char**)malloc(sizeof(char(*)*nv));
        if (tabSkeyElecteurs == NULL ) return;
        for(int i=0;i<nv;i++){
            tabSkeyElecteurs[i]=NULL;
        }
        // generations de couples de cles publiques et secretes des electeurs
        for(int i=0;i<nv;i++){
            init_pair_keys(pkey,skey,3,7);

        }
        char* 

    }



}







int main(){

return 0 ;
}