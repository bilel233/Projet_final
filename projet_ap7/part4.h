#include <stdio.h>
#include <stdlib.h>
#include "part2.h"
#include"part1.h"
#include "part3.h"
#include <math.h>
#include <time.h>
#include <string.h>

typedef struct cellKey {
    KEY * data ;
    struct cellKey * next ;
 } CellKey ;

 CellKey* create_cell_key(KEY* key);

typedef struct cellProtected {
    PROTECTED * data ;
    struct cellProtected * next ;
} CellProtected ;

CellProtected* inserer_tete_P(CellProtected* cp,PROTECTED* p);