#ifndef NW_UTIL
#define NW_UTIL

#include <stdlib.h>
#include <string.h>

unsigned long DJBHash(char *str);

unsigned long DEKHash(char* str) ;

unsigned long SDBMHash(char* str) ;

unsigned long ELFHash(char* str) ;

#endif //end of NW_UTIL
