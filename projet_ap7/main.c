#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part2.h"
#include <time.h>
#include <math.h>
#include "part3.h"
#include "part4.h"
#include "part1.h"

void generate_random_data(int nv,int nc){
    /* genere des couples de cles puis realisela creation de fichiers */

    if(nc>nv){
        printf("fonction generate_random_data: Erreur nc ne doit pas etre inferieur a nv\n");
        return;
    }
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
        char ** tabSkeyElecteurs = (char**)malloc(sizeof(char*)*nv);
        if (tabSkeyElecteurs == NULL ) return;
        for(int i=0;i<nv;i++){
            tabSkeyElecteurs[i]=NULL;
        }
        // generations de couples de cles publiques et secretes des electeurs
        for(int i=0;i<nv;i++){
            init_pair_keys(pkey,skey,3,7);
            char* StrPKeyElecteur = key_to_str(pkey);
		
            char* StrSkeyElecteur = key_to_str(skey);
            
            tabClesElecteurs[i] = strdup(StrPKeyElecteur);

            tabSkeyElecteurs[i] = strdup(StrSkeyElecteur);
            
            fprintf(f1,"%s %s\n", StrPKeyElecteur, StrSkeyElecteur);
            free(StrPKeyElecteur);
            free(StrSkeyElecteur);

            printf("Counter = %d\n", i);
        }
    char** tabClesCand =malloc( nv * sizeof(char*));
	for (int i = 0; i < nv; ++i){
        tabClesCand[i] = NULL;
    }
    //Selection de nc cle publique pour definir les nc candidats parmis les nv citoyens
	for(int j = 0; j < nc; j++)
	{
		int random = (rand() % nv);
 
        while (tabClesCand[random] != NULL) //Tant que cette case n'est pas nulle on en cherche une autre...
		{
			random = rand() % nv;
		}

		//Candidat choisi d'index random <=> Citoyen d'index random
		tabClesCand[random] = strdup(tabClesElecteurs[random]);

		//Maj du fichier
		fprintf(f2, "%s\n", tabClesCand[random]);
	}

    //kjk
	


char** tabCleCand2 =malloc(nv * sizeof(char*));
	for (int i = 0; i < nv; ++i){
		tabCleCand2[i] = NULL;
    }

	int tabCleCandindex2 = 0;
	for (int k = 0; k < nv; k++)
	{
		if (tabClesCand[k] == NULL)
		{
			printf("%d est NULL\n", k);
		}else{
			printf("%s\n",tabClesCand[k]);

			tabCleCand2[tabCleCandindex2++] = strdup(tabClesCand[k]);
		}
	}	

	//Generation des declarations pour chaque citoyen
	for (int i = 0; i < nv; i++)
	{	
		KEY* pKeyElec = str_to_key(tabClesElecteurs[i]);
		KEY* sKeyElec = str_to_key(tabSkeyElecteurs[i]);

		int randCandidate = rand() % nc;

        
		SIGNATURE* sgn = sign(tabCleCand2[randCandidate], sKeyElec);


		PROTECTED* pr = init_protected(pKeyElec, tabCleCand2[randCandidate], sgn);

		char* prCitoyen = protected_to_str(pr);

		fprintf(f3, "%s\n", prCitoyen);


		char* pKeyPr = key_to_str(pr->pKey);

		if(verify(pr)==1)
		{
			printf("Verification de mess: %s, de pKey: %s, est valide? Oui\n", pr->mess, pKeyPr);
		}
		else
		{
			printf("Verification de mess: %s, de pKey: %s, est valide? Non\n", pr->mess, pKeyPr);
		}
	
		free(pKeyPr);

		free(pKeyElec);
		free(sKeyElec);
		free(prCitoyen);
	}
		
	for(int i = 0; i < nc; i++)
    {
		free(tabCleCand2[i]);
	}
	free(tabCleCand2);

	for(int i = 0; i < nv; i++)
    {
		free(tabClesCand[i]);
	}
	free(tabClesCand);
	
	for(int j = 0; j < nv; j++)
    {
		free(tabClesElecteurs[j]);
	}
	free(tabClesElecteurs);

	for(int k = 0; k < nv; k++)
    {
		free(tabSkeyElecteurs[k]);
	}
	free(tabSkeyElecteurs);

	free(pkey);
	free(skey);
    
	fclose(f1);
	fclose(f2);
	fclose(f3);
}





int main()
{
    //srand(time(NULL));
    //generate_random_data(100,20);

    //CellKey *ckey=read_public_keys("keys.txt");
    //print_list_keys(ckey);

    //delete_list_keys(ckey);

   // CellProtected* cProtected=read_protected();
   // print_list_protected(cProtected);

	//delete_unvalid_sgn(cProtected);

	//print_list_protected(cProtected);
	//delete_list_protected(cProtected);


	//free(cProtected);//A AMELIORER 
	
    return 0;
}







