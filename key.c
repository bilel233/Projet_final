#include"key.h"


int main(int argc,char *argv[]){
    KEY *key = &(KEY){.m = 7, .n= 31}; // initialiser key afin de ne pas avoir
    //un Bus error 10  
    init_key(key,10,7);

    return 0;


}
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
    if (vall == NULL) return NULL;
    sprintf(val,"(%lx,%lx",key->m,key->n);
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
SIGNATURE* init_signitature(long* content,int size){
    /* alloue puis remplie une signature
        */

    SIGNATURE *s = (SIGNATURE*)malloc(sizeof(SIGNATURE));
    if (s==NULL) return NULL;
    s->size=size;
    s->content=content;
    return s;
}
SIGNATURE* sign(char* mess,KEY* sKey){
    /* creee une signature a partir du message et de la cle secrete de l'emetteur
        */
    return init_signitature(encrypt(mess,sKey->m,sKey->n),strlen(mess));
}
void free_signature(SIGNATURE* sgn){
    /* libere une signature 
        */
    free(sgn->content);
    free(sgn);
}



