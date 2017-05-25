#include "myassert.h"
#include <stdio.h>
#include <stdlib.h>

void aFalse(char *file, int line){
    printf("Failure: File %s assertion error at line %d\n",file, line);
}
