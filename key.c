#include "key.h"
#include "proj.h"
#include "rsa.h"
#ifndef KEY_H
#define KEY_H

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
#endif