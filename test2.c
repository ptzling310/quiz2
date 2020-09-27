#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t hexchar2val(const char str[])
{
   uint64_t result = 0 ; 
   int i=0;
  
  for(int i = 2 ; i < strlen(str) ; i++){
      const uint8_t letter = str[i]& 0x40;
	  const uint8_t shift  = (letter >> 3 ) | (letter >> 6);

	  result = (result << 4) | ( (str[i]+shift)&0xf);
   }

   return result;
}

void main()
{
   printf("0xa = %ld\n",hexchar2val("0xa"));
   printf("0xCAFEBABE = %ld\n",hexchar2val("0xCAFEBABE"));
}
