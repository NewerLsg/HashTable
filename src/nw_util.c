#include "nw_util.h"

unsigned long 
DJBHash(char *str) {
      unsigned long hash = 5381;  
      int i ;
      for( i = 0; i < strlen(str); i++)  
      {  
         hash = ((hash << 5) + hash) + str[i];  
      }  

      return hash;  
}

unsigned long 
DEKHash(char* str)  
 {  
     unsigned long hash = strlen(str);  
      int i = 0;

      for(; i < strlen(str); i++)  
      {  
         hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];  
      }  
      return hash;  
 }  

unsigned long 
SDBMHash(char* str)  
   {  
      long hash = 0;  
      int i;
      for( ; i < strlen(str); i++)  
      {  
         hash = str[i] + (hash << 6) + (hash << 16) - hash;  
      }  
      return hash;  
   }  

unsigned long 
ELFHash(char* str)  
{  
	long hash = 0;  
      long x    = 0, i = 0;  
      for(; i < strlen(str); i++)  
      {  
         hash = (hash << 4) + str[i];  
         if((x = hash & 0xF0000000L) != 0)  
         {  
            hash ^= (x >> 24);  
         }  
         hash &= ~x;  
      }  
      return hash;  
}  