#ifndef KEY_H
#define KEY_H
#include <stdio.h>
#include <stdlib.h>
#include "rsa.h"
#include"proj.h"
#include <math.h>
#include <time.h>
#include <string.h>
/* definition des protypes des fonctions */

typedef struct key  {
    long m;// represente ou bien la cle privee ou bien la cle publique
    long n;
}KEY;

typedef struct signature{
    long* content;
    long size;
}SIGNATURE;

void init_key(KEY* key, long val, long n);
void init_pair_keys(KEY* pkey, KEY* skey, long low_size,long up_size);
char* key_to_str(KEY* key);
SIGNATURE* init_signitature(long* content,int size);
SIGNATURE* sign(char* mess,KEY* sKey);
void free_signature(SIGNATURE* sgn);


#endif
