#include "part1.h"
#include "part2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(){
    srand(time(NULL));

    //Testing Init Keys
    KEY * pKey = malloc(sizeof(KEY));
    KEY * sKey = malloc(sizeof(KEY));
    init_pair_keys( pKey , sKey ,3 ,7);
    printf("%lx\n",pKey->n);
    printf("pKey : %lx , %lx\n", pKey->m,pKey->n) ;
    printf ("sKey : %lx , %lx\n",sKey->m,sKey->n) ;

    //Testing Key Serialization

    char *chaine= key_to_str(pKey);
    printf ("key to str: %s \n",chaine);
    KEY *k = str_to_key(chaine);
    printf ("str to key : %lx , %lx\n",k->m,k->n);

    //Testing signature
    //Candidate keys:
    KEY *pKeyC =malloc(sizeof(KEY));
    KEY *sKeyC =malloc(sizeof(KEY));
    init_pair_keys(pKeyC,sKeyC,3,7);
    //Declaration:
    char *mess= key_to_str(pKeyC);
    printf("mess:%s\n",mess);
    printf ("%s vote pour %s \n", key_to_str(pKey),mess);
    SIGNATURE *sgn=sign(mess , sKey);
    printf ("signature: ") ;
    print_long_vector(sgn->content,sgn->size);
    chaine = signature_to_str(sgn);
    printf ("signature to str : %s \n",chaine);
    sgn = str_to_signature(chaine);
    printf ("str to signature");
    print_long_vector(sgn->content ,sgn->size);


    //Testing protected:
    PROTECTED * pr = init_protected(pKey,mess,sgn);
    //Verification:
    if(verify(pr)) 
    {
        printf("Signature valide\n");
    }
    else 
    {
        printf("Signature non valide\n");
    }
    chaine = protected_to_str(pr);
    printf ("protected to str: %s\n", chaine);
    pr = str_to_protected(chaine);
    printf("str to protected : %s %s %s \n",key_to_str(pr->pKey),pr->mess,signature_to_str(pr->s));

    
    free(mess);
    free(chaine);
    free(pr->mess);
    free(pr);
    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);
    return 0;

}
