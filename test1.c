#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

bool is_alpha(const char str[],size_t size)
{
   if(size==0)
      return false;

   int i = 0;
   while( i+8  <=size){
   
      uint64_t payload;
      memcpy(&payload, str + i, 8);

      uint64_t A = payload + PACKED_BYTE(128 - 'A' + 0 ); 
      uint64_t Z = payload + PACKED_BYTE(128 - 'Z' + (-1)); 
	  uint64_t a = payload + PACKED_BYTE(128 - 'a' + 0);
      uint64_t z = payload + PACKED_BYTE(128 - 'z' + (-1));

      uint64_t mask_up = ((A ^ Z) & PACKED_BYTE(0x80));
      uint64_t mask_low = ((a ^ z) & PACKED_BYTE(0x80));

      if(mask_up == PACKED_BYTE(0x00) &&  mask_low== PACKED_BYTE(0x00))
         return false;

	  i+=8;
   }

   while (i < size) {
      if ( (str[i] < 65 || (str[i] > 90 && str[i] < 97) || str[i] > 122))
         return false;
      i++;
   }

   return true;

}

void main()
{
  char a[]={"testING"};
  if(is_alpha(a,strlen(a)))
     printf("a: TRUE\n");
  else 
     printf("a: FALSE\n");
  char b[]= {"@@deF"};
  if(is_alpha(b,strlen(b)))
     printf("b: TRUE\n");
  else
     printf("b: FALSE\n");

}
