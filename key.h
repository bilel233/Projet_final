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

void init_key(KEY* key, long val, long n);

#endif
