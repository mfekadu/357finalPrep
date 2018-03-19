#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void printCWD() {
   char cwd[PATH_MAX];
   if ( getcwd(cwd, sizeof(cwd)) == NULL ) {
      perror("getcwd");
   }
   printf("curr dir = %s\n", cwd);
}

/* 0 on success, -1 on failure */
int cdTidle(char *path) {
   char buf[PATH_MAX];
   pid_t child;
   int status;

   strcpy(buf, "//home/");
   
   printCWD();

   if ( chdir( strcat(buf, path) ) == -1 ) {
      return -1;
   }

   if ((child = fork()) < 0 ) {
      perror("fork error");
      exit(EXIT_FAILURE);
   }
   else if ( child == 0 ) {
      /* child stuff */
      /* specify pathname, specify arguments */
      printf (" I AM LUKE SKYWALKER %d\n", child);
      printf ("execvp `cd` %s", buf);
      execvp("cd", (char *[]){"cd", buf, NULL});
      perror("cd");
      exit(EXIT_FAILURE);
   }
   else {
      /* parent stuff */
      printf (" LUKE I AM YOUR FATHER %d\n", child );
      while (wait(&status) < 0);
   }

   /* again for ls */
   if ((child = fork()) < 0 ) {
      perror("fork error");
      exit(EXIT_FAILURE);
   }
   else if ( child == 0 ) {
      /* child stuff */
      /* specify pathname, specify arguments */
      execvp("ls", (char *[]){ "ls", "-l", NULL });
      perror("ls");
      exit(EXIT_FAILURE);
   }
   else {
      /* parent stuff */
      while (wait(&status) < 0);
   }
 
   printCWD();

   return 0;
}

int main(int argc, const char *argv[]) {
   if (argc < 2) {
      printf("you suck, gimme 2 args!\n");
      exit(0);
   }

   printf ( "cdTilde output = %d\n", cdTidle( (char *) argv[1]) );
   return 0;
}
