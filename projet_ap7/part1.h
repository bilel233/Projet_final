#ifndef PROJ_H
#define PROJ_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>
// prototype des fonctions
int is_prime_naive(long p);
long plus_grand();
long modpow_naive(long a, long m, long n);
long modpow(long a, long m, long n);
char* ecritureModpowNaive(char *fichier);
int witness(long a, long b,long d,long p);
char *ecritureModpow(char* fichier);
long rand_long(long low,long up);
long random_prime_number(int low_size, int up_size, int k);
long power(long a,long b);
int is_prime_miller(long p, int k);
long randomprime(int low_size,int up_size,int k);
#endif