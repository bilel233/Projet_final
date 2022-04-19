#include "part3.h"


void init_key(KEY* key, long val, long n){
    // Initialise une cle deja alloué
    if (key != 0){
        key -> m = val;
        key -> n = n;
    }
}
void init_pair_keys(KEY* pkey, KEY* skey, long low_size,long up_size){
    /* utilise le protocole rsa pour initialiser une cle publique puis cle secrete
        */

    long p = random_prime_number(low_size,up_size,5000);
    long q = random_prime_number(low_size,up_size,5000);
    while(p==q){
        q=random_prime_number(low_size,up_size,5000);
    }
    long n,s,u;
    generate_key_values(p,q,&n,&s,&u);
    if(u<0){
        long t= (p-1)*(q-1);
        u=u+t; // s*u mod t = 1

    }
    init_key(pkey,s,n);
    init_key(skey,u,n);
    

}
char* key_to_str(KEY* key){
    /* passe d'une variable de type KEY a sa representation sous forme de chaine de caractere
        */
    char *val=(char*)malloc(sizeof(char)*256);
    if (val == NULL) return NULL;
    sprintf(val,"(%ld,%ld",key->m,key->n);
    return val;
}



KEY* str_to_key(char* str){
    /* realise le passage inverse
        */
    long val;
    long n;
    sscanf(str,"(%lx,%lx)",&val,&n);
    KEY *k = (KEY*)malloc(sizeof(KEY));
    if (k == NULL) return NULL;
    init_key(k,val,n);
    return k;

}
SIGNATURE* init_signature(long* content, int size)
{
    SIGNATURE *sign=malloc(sizeof(SIGNATURE)); 
    sign->size=size;

    for(int i=0;i<size;i++)
    {
        sign->content[i]=content[i];
    }

    return sign;
}
SIGNATURE* sign(char* mess, KEY* sKey)
{
    mess=key_to_str(sKey);
    long *crypted=encrypt(mess,sKey->m,sKey->n);
    int len=strlen(mess)+1;
    SIGNATURE *s=init_signature(crypted,len);

    return s;
}

void free_signature(SIGNATURE* sgn){
    /* libere une signature 
        */
    free(sgn->content);
    free(sgn);
}
char* signature_to_str(SIGNATURE* sgn){
    /* passe d'une Signature à sa representation sous forme de chaines de caracteres
        */
    char* result = malloc(10*sgn->size*sizeof(char));
    result[0]='#';
    int pos=1;
    char buffer[156];
    for(int i=0; i<sgn->size; i++){
        sprintf(buffer,"%lx",sgn->content[i]);
        int len=strlen(buffer);
        for (int j = 0; j<len; j++){
            result[pos]=buffer[j];
            pos++;
        }
        result[pos]='#';
        pos++;
    }
    result[pos]='\0';
    result = realloc(result,(pos+1)*sizeof(char));
    return result;
}

SIGNATURE* str_to_signature(char* str){
    /*passe d'une chaine de caracteres à une SIGNATURES
        */
    int len = strlen(str);
    long* content = (long*)malloc(sizeof(long)*len);
    int num=0;
    char buffer[256];
    int pos=0;
    for (int i=0; i<len; i++){
        if (str[i]!='#'){
            buffer[pos]=str[i];
            pos++;
        }
        else{
            if (pos!=0){
                buffer[pos]= '\0';
                sscanf(buffer,"%lx", &(content[num]));
                num++;
                pos=0;
            }
        }
        
    }
    content=realloc(content,num*sizeof(long));
   return init_signature(content,num);
}

PROTECTED* init_protected(KEY* pKey, char* mess, SIGNATURE* sgn){
    /* alloue puis initialise la structure 
        */
    PROTECTED* p = (PROTECTED*)malloc(sizeof(PROTECTED));
    p->pKey = pKey;
    p->mess = mess;
    p->s = sgn;
    return p;
}
int verify(PROTECTED* pr){
    /* verifie la signature contenue dans pr
        */
    char *d = decrypt(pr->s->content,pr->s->size,pr->pKey->m,pr->pKey->n);
    int i= (strcmp(d,pr->mess)==0);
    free(d);
    return i;
}
char *protected_to_str(PROTECTED * pr){
    /* permet de passer d'un protected a sa representation sous chaine de caracteres
        */
    char* buffer=(char*)malloc(sizeof(char)*256);
    char *sgn=signature_to_str(pr->s);
    char *key=key_to_str(pr->pKey);
    sprintf(buffer,"%s %s %s",key,pr->mess,sgn);
    free(sgn);
    free(key);
    return buffer;

}
PROTECTED* str_to_protected(char* c) {
    /* realise le chemin inverse */
    char pKey[256];
    char mess[256];
    char sign[256];
    sscanf(c ,"%s %s %s", pKey, mess, sign);
    char* M=(char*)malloc(sizeof(char)*strlen(mess));
    M=strdup(mess);
    PROTECTED* res = init_protected(str_to_key(pKey), M, str_to_signature(sign));
    return res;
}
void free_protected(PROTECTED* pr){
    /* libere la structure */
    free_signature(pr->s);
    free(pr->mess);
    free(pr->pKey);
    free(pr);
}

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
        f3= fopen("declarations.txt","w");

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


