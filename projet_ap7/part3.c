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

