 #include"key.h"


/*int main(int argc,char *argv[]){
    KEY *key = &(KEY){.m = 7, .n= 31}; // initialiser key afin de ne pas avoir
    //un Bus error 10  
    init_key(key,10,7);

    return 0;


}
*/
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
	char* str=malloc(sizeof(char));
	sprintf(str,"(%lx,%lx)",key->val,key->n);
	return str;
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


SIGNATURE* init_signature(long* content, int size){
    SIGNATURE *sign=malloc(sizeof(SIGNATURE)); 
    sign->size=size;

    for(int i=0;i<size;i++)
    {
        sign->content[i]=content[i];
    }

    return sign;
}

SIGNATURE* sign(char* mess, Key* sKey){
    mess=key_to_str(sKey);
    long *crypted=encrypt(mess,sKey->val,sKey->n);
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





char *signature_to_str( SIGNATURE *sgn) {
    char * result = malloc(10*sgn->size * sizeof(char));
    result [0]='#';
    int pos = 1;
    char buffer [156];
    for(int i =0; i < sgn->size;i++) {
        sprintf(buffer ,"%lx",sgn->content[i]) ;
        for(int j=0;j < strlen(buffer);j++){
            result[pos]=buffer[j];
            pos = pos +1;
        }
        result[pos]='#';
        pos = pos+1;
    }
    result[pos] ='\0';
    result =realloc(result,(pos+1)*sizeof(char));
    return result;
}

SIGNATURE *str_to_signature(char *str) {
    int len = strlen ( str );
    long * content = ( long *)malloc(sizeof(long)*len);
    int num = 0;
    char buffer [256];
    int pos = 0;
    for (int i =0; i < len ; i ++)  {
        if(str[i]!='#') {
            buffer[pos]=str[i];
            pos = pos +1;
        } 
        else 
        {
            if( pos != 0){
                buffer[pos]='\0';
                sscanf(buffer,"%lx",&(content[num]));
                num = num + 1;
                pos = 0;
            }
        }
    }
    content = realloc(content,num*sizeof(long));
    
    return init_signature(content,num);
}

Protected* init_protected(Key* pKey, char* mess,SIGNATURE* sgn){
    Protected *p=malloc(sizeof(Protected));
    p->pKey=pKey;
    p->mess=strdup(mess);
    p->sgn=sgn;

    return p;
}

int verify(Protected* pr){
    char *msg=pr->mess;
    
    int len=strlen(msg);
    if(strcmp(msg,decrypt(pr->sgn->content,len,pr->pKey->val,pr->pKey->n))==0)
    {
        return 1;
    }

    return 0;
}

char* protected_to_str(Protected *pr)
{
    char* keys=key_to_str(pr->pKey);
    char* signs=signature_to_str(pr->sgn);
    char* result=malloc(sizeof(char));
    sprintf(result,"%s %s %s",keys,pr->mess,signs);


    return result;
}

Protected* str_to_protected(char* str){
    char* keys=malloc(sizeof(char));
    char* signs=malloc(sizeof(char));
    char* mess=malloc(sizeof(char));

    sscanf(str,"%s%s%s",keys,mess,signs);

    Key* pKey=str_to_key(keys);
    SIGNATURE *sig=str_to_signature(signs);

    Protected *p=init_protected(pKey,mess,sig);

    return p;
}
