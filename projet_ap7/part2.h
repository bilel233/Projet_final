#ifndef PART2_H
#define PART2_H
#include <stdio.h>
#include <stdlib.h>
#include "part1.h"
#include <math.h>
#include <time.h>
#include <string.h>
// prototype des fonctions 
long extended_gcd(long s,long t,long *u, long *v);
long* encrypt(char* chaine, long s, long n);
char* decrypt(long* crypted, int size,long u, long n);
void print_long_vector(long* result , int size);
void generate_key_values(long p,long q,long* n,long *s,long* u);

#endif


