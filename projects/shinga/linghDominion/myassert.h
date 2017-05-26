#ifndef _MYASSERT_H
#define _MYASSERT_H


#define ASSERTTRUE(expr) \
	if(!(expr)) \
	aFalse(__FILE__, __LINE__)


void aFalse(char *file, int line);





#endif
