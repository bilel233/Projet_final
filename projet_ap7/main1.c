#include "part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    srand(time(NULL));
    long m = modpow(5,2,4);
    long b = modpow_naive(5,2,4);
    printf("%ld\n",random_prime_number(10,30,50));
    printf("%ld\n",random_prime_number(10,30,50));

    printf("%ld %ld",m,b);
    return 0;

}