#ifndef RSA_H
#define RSA_H
#include <stdio.h>
#include <stdlib.h>
#include "proj.h"
#include <math.h>
#include <time.h>
#include <string.h>
// prototype des fonctions 
long extended_gcd(long a,long t,long *u, long *v);
void generate_key_values(long p,long q,long* n,long *s,long* u);
long* encrypt(char* chaine, long s, long n);
char* decrypt(long* crypted, int size,long u, long n);

#endif
