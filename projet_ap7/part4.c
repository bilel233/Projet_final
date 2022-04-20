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

int find_position(HashTable *t, KEY *key)   {

    int indice = hash_function(key, t->size);
    
    int i=0;
    while(i < t->size)    {
        assert(((indice + i) % t->size) >= 0);
        //on parcourt au plus toute la table a partir de la case indice (hash + 0)
        if (t->tab[(indice + i) % t->size] != NULL) {
            //key->m correspond a key->val (le nom etait dans les exemples et non dans l'enonce)
            if (  (t->tab[(indice + i) % t->size]->key->m == key->m) && (t->tab[(indice + i) % t->size]->key->n == key->n)  ) {
                return (indice + i) % t->size; //la cle est deja presente dans la table
            } 
        } else { 
            return (indice + i) % t->size; //emplacement libre pour inserer la cle
        }
        i++;
    }
    fprintf(stderr,"Erreur : find_position : pas de position trouvee\n");
    return -1;  //indication d'erreur
}

HashTable *create_hashtable(CellKey *keys, int size)    {
    //creation de la table de hachage

    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->tab = (HashCell **)malloc(size*sizeof(HashCell *));

    for (int i=0; i<size; i++)  {
        table->tab[i] = NULL;
    }
    table->size = size;

    //insertion des cles de la liste keys
    int pos;
    while (keys)    {
        pos = find_position(table, keys->data);

        if (pos == -1)  {
            printf( "Erreur : create_hashtable, pas de position trouvee\n");
            for (int i=0; i<table->size; i++)   {
                free(table->tab[i]);
            }
            free(table->tab);
            free(table);
            return NULL;
        }
        //Si la cle n'est pas dans la table on l'ajoute
        if (table->tab[pos] == NULL)    {    
            HashCell *candidate = create_hashcell(keys->data);
            table->tab[pos] = candidate;
        }
        keys = keys->next;
    }
    return table;
}   
KEY *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)    {
   

    //creation des deux tables de hachage candidats votants
    HashTable *hc = create_hashtable(candidates,sizeC);
    HashTable *hv = create_hashtable(voters, sizeV);

    //parcours des declarations
    int posV, posC;
    KEY *keyC;

    //parcours de la liste de declarations
    while (decl)    {
        posV = find_position(hv, decl->data->pKey); 
        if (hv->tab[posV] != NULL)   {
            if (hv->tab[posV]->val == 0) {            //il n'a jamais vote
                keyC = str_to_key(decl->data->mess);
                posC = find_position(hc,keyC);
                free(keyC);
                if(hc->tab[posC] != NULL)   {     //si le candidat existe
                    hv->tab[posV]->val = 1;       //il a vote
                    hc->tab[posC]->val = hc->tab[posC]->val + 1; //le candidat a un vote de plus              

                }
            }   
        }
        decl = decl->next;
    }

    //determination du gagnant    //ET SI DEUX CANDIDATS SONT EX AEQUO --on prend le premier dans la table
    HashCell *gagnant = NULL;
    int val_gagnant = -1;
    for (int i=0; i<hc->size; i++)  {
        if (hc->tab[i] != NULL){
            if (val_gagnant < hc->tab[i]->val) {
                gagnant = hc->tab[i];
                val_gagnant = hc->tab[i]->val;
            }
        }
    }
    if (gagnant == NULL){
        fprintf(stderr,"Erreur : compute_winner : gagnant null");
    }

    KEY *g = gagnant->key;
    //on ne free pas les cles qui sont stockes egalement dans les listes 
    delete_hashtable(hc);   
    delete_hashtable(hv);
    return g;
}




