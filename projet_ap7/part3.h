#ifndef KEY_H
#define KEY_H
#include <stdio.h>
#include <stdlib.h>
#include "part2.h"
#include"part1.h"
#include <math.h>
#include <time.h>
#include <string.h>
/* definition des protypes des fonctions */

typedef struct key {
    long m;// represente ou bien la cle privee ou bien la cle publique
    long n;
}KEY;

typedef struct signature{
    long* content;
    int size;
}SIGNATURE;

typedef struct protected{
    KEY* pKey;
    char* mess;
    SIGNATURE* s;
}PROTECTED;


void init_key(KEY* key, long val, long n);
void init_pair_keys(KEY* pkey, KEY* skey, long low_size,long up_size);
KEY* str_to_key(char* str);
SIGNATURE* init_signitature(long* content,int size);
SIGNATURE* sign(char* mess,KEY* sKey);
void free_signature(SIGNATURE* sgn);
char* signature_to_str(SIGNATURE* sgn);
SIGNATURE* str_to_signature(char* str);
char* key_to_str(KEY* key);
int verify(PROTECTED* pr);
PROTECTED* init_protected(KEY* pKey, char* mess, SIGNATURE* sgn);
char *protected_to_str(PROTECTED * pr);
void free_protected(PROTECTED* pr);





#endif
