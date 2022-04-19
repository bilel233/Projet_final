#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "part1.h"
#include "part2.h"
#include "part3.h"
#include "part4.h"




int main()
{
    //srand(time(NULL));

	
    generate_random_data(100,20);

    //CellKey *ckey=read_public_keys("keys.txt");
    //print_list_keys(ckey);

    //delete_list_keys(ckey);

   // CellProtected* cProtected=read_protected();
   // print_list_protected(cProtected);

	//delete_unvalid_sgn(cProtected);

	//print_list_protected(cProtected);
	//delete_list_protected(cProtected);


	//free(cProtected);//A AMELIORER 
	
    return 0;
}







