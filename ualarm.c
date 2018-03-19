#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define MS 500000

long ualarm(long usec) {
   sleep((int) usec/100000 );
   raise(SIGALRM);
   return usec;
}




int main (int argc, char *argv[]) {

   /* I was just testing how the alarm func works here */
   /* alarm(5); */

   ualarm( (long) 900000); 

   return 0;
}
