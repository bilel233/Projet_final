#include "part4.h"
#include <string.h>

CellKey* create_cell_key(KEY* key){
    CellKey *k = malloc(sizeof (CellKey));

    if(k== NULL){
        return NULL;
    }
    k->data=key;
    k->next=NULL;

    return k;

}


CellKey * ajouter_tete(CellKey ** list ,KEY *k){
    CellKey * final= create_cell_key(k);
    final->next=*list;
    *list=final;

    return *list;
   
}

CellKey* read_public_keys(char* filename){

    if (strcmp(filename, "keys.txt") != 0 && strcmp(filename, "candidates.txt") != 0){
		printf("Fonction read_public_keys: Erreur de fichier: %s\n", filename);
		return NULL;
	}

	FILE* file = fopen(filename, "r");
	if (!file)
	{
		printf("Fonction read_public_keys: Erreur ouverture fichier: %s\n", filename);
		return NULL;
	}

	char buffer[256];
	long p,n;

	CellKey* cellKey = NULL;

	int count = 0;

    while (fgets(buffer, 256, file))
    {
        sscanf(buffer, "(%ld,%ld)", &p, &n);
        KEY* publicKey =malloc(sizeof(KEY));
        init_key(publicKey, p, n);

   	    if (!cellKey)
   	    {
   		    cellKey = create_cell_key(publicKey);
   	    } 
        else 
        {
   		    ajouter_tete(&cellKey, publicKey);
   	    }
   	    count++;
   	    //printf("%d\t",count);
    }
    
    printf("total: %d\n",count);
    fclose(file);
    return cellKey;
}


void print_list_keys(CellKey* LCK){
    if(LCK==NULL)
    {
        printf("Erreur LCK NULL");
        return;
    }
    
    CellKey *ptr=LCK;
    while(ptr!=NULL)
    {
        KEY* k=ptr->data;
        //printf("%lx\n",ptr->data->val);
        printf("(%lx, %lx)\n", k->m, k->n);
        ptr=ptr->next;
    }
  printf("\n");
}

//on supprime le premier element de la liste
void delete_cell_key(CellKey* c)
{
    if(!c)
    {
        printf("cellkey est NULL\n");
    }
    free(c->data);
    free(c);
}

//Supprimation de la liste des cles
void delete_list_keys(CellKey* c)
{
    if(!c)
    {
        printf("Cellkey deja vide\n");
    }
    while(c!=NULL)
    {
        CellKey* tmp=c->next;
        delete_cell_key(c);
        c=tmp;
    }
}

//liste de protected
CellProtected* create_cell_protected(PROTECTED* pr)
{
    CellProtected *p=malloc(sizeof(CellProtected));
    if (!p)
    {
        printf("erreur allocation\n");
        return NULL;
    }

    p->data=pr;
    p->next=NULL;
    return p;
}


CellProtected* inserer_tete_P(CellProtected* cp,PROTECTED* p){
    if(cp==NULL){
        return create_cell_protected(p);
    }
    CellProtected* tete=create_cell_protected(p);
    tete->next=cp;
    return tete;
}


CellProtected* read_protected(char* fic){
if(strcmp(fic,"declaration.txt")!=0){
        printf("Mauvais fichier");
        return NULL;
    }
    FILE* data= fopen(fic,"r"); //mode ouverture
    if (data == NULL) {
        printf("Erreur a l'ouverture du fichier\n" );
        return NULL;
    }
    CellProtected* cellP;
    int val;
    char ligne[256];
    char pKey[256];
    char sign[256];
    char mess1[256];

    while(fgets(ligne,256,data)!=NULL){
        if(sscanf(ligne,"%d %s %s %s",&val,mess1,sign,pKey)==4){
            KEY* key=str_to_key(pKey);
            char* mess= strdup(mess1);
            SIGNATURE* sgn=str_to_signature(sign);
            PROTECTED* pr=init_protected(key,mess,sgn);      
            cellP=inserer_tete_P(cellP,pr);
    
        }
    }
    fclose(data);
    return cellP;
}


void print_list_protected(CellProtected* c)
{
    if(c==NULL)
    {
        printf("Erreur\n");
        return;
    }
    CellProtected* ptr=c;

    char* str=malloc(sizeof(char)*256);
    int cpt=0;
    while(ptr!=NULL)
    {
        str=protected_to_str(ptr->data);
        printf("%s\n",str);
        ptr=ptr->next;
        cpt++;
    }
    //printf("NULL\n");
    printf("total %d\n",cpt);
    free(str);
}


//on supprime le premier element de la liste (c'est plus simple)  
void delete_cell_protected(CellProtected* c)
{
    if(c!=NULL)
    {
        //Key* pKey;
        //char* mess;
        //Signature* sgn;
        free(c->data->pKey);
        free(c->data->mess);
        free(c->data->s);
        free(c->data);
        free(c);
    
    }
}

void delete_list_protected(CellProtected* c)
{
    while(c!=NULL)
    {
        CellProtected* tmp=c->next;
        delete_cell_protected(c);
        c=tmp;
    }  
}

HashCell* create_hashcell(KEY* key){
    /*alloue une cellule de la table de hachage puis initialise tout ses champs */
    HashCell *c = (HashCell*)malloc(sizeof(HashCell));
    if(c==NULL) return NULL;
    // on instancie les champs de la cellule
    c->key=key;
    c->val=0;
return c;

}

int hash_function(KEY* key, int size){
    /* retourne la position d’un élément dans la table de hachage. */
   return (key->m + key->n) % size;
}