#ifndef PART4_H
#define PART4_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "part1.h"
#include "part2.h"
#include "part3.h"

typedef struct cellKey {
    KEY* data ;
    struct cellKey * next ;
 } CellKey ;

typedef struct hashcell {
    KEY* key ;
    int val ;
}HashCell ;

typedef struct hashtable {
HashCell**tab;
int size;
}HashTable;

typedef struct cellProtected {
    PROTECTED * data ;
    struct cellProtected * next ;
} CellProtected ;
CellKey* create_cell_key(KEY* key);
CellProtected* inserer_tete_P(CellProtected* cp,PROTECTED* p);
CellKey * ajouter_tete(CellKey ** list ,KEY *k);
CellKey* read_public_keys(char* filename);
void print_list_keys(CellKey* LCK);
void delete_list_keys(CellKey* c);
CellProtected* create_cell_protected(PROTECTED* pr);
CellProtected* read_protected(char* fic);
void print_list_protected(CellProtected* c);
void delete_cell_protected(CellProtected* c);
void delete_list_protected(CellProtected* c);
HashCell* create_hashcell(KEY* key);
int hash_function(KEY* key, int size);
int find_position(HashTable* t, KEY* key);
HashTable* create_hashtable(CellKey* keys, int size);
void delete_hashtable(HashTable* t);
KEY *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);

#endif




