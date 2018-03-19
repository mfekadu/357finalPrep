#include <stdio.h>

typedef struct bit *bitlist;
struct bit {
   int b;
   bitlist next;
};


int makeint(bitlist bits) {
   int i = 0;
   int skip = 1;
   int buf = 0; 

   while (bits) {
      if (skip && bits->b == 0) {
         bits = bits->next;
         printf("skip\n");
      }
      else if (skip && bits->b == 1) {
         printf("set skip to 0\n");
         skip = 0;
      }
      else {
         if (i < sizeof(int)*8) {
            buf <<= 1;
            buf += bits->b;
            i++;
            printf("buf << 1; buf += %d\t buf = %d\n", bits->b, buf);
            bits = bits->next;
         }
      }
   }
   return buf;
}

void main(){ 

   struct bit b8 = { .b = 0, .next = NULL };
   struct bit b7 = { .b = 0, .next = &b8 };
   struct bit b6 = { .b = 0, .next = &b7 };
   struct bit b5 = { .b = 0, .next = &b6 };
   struct bit b4 = { .b = 0, .next = &b5 };
   struct bit b3 = { .b = 0, .next = &b4 };
   struct bit b2 = { .b = 0, .next = &b3 };
   struct bit b1 = { .b = 1, .next = &b2 };
   
   bitlist bits = &b1;

   printf("makeint = %d\n", makeint(bits));

}
