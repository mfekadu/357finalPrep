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

#define LSTAT_ERROR "why the fudge do you want to check if the" \
                     " PREVIOUS DIRECTORY is a LEAF?!?" \
                     " lstat only works with the current working dir."

int is_leaf_directory(const char *path) {


      DIR *d;
      struct dirent *entry;
      struct stat sb;
      char cwd[PATH_MAX];
      
      /*if path too long*/
      if(strlen(path) > PATH_MAX) {
         printf("path too long\n");
         return 0;
      }

      /* have to chdir to make lstat work for any path */
      if (chdir(path) == -1) {
         printf("chdir fail\n");
         perror(path);
         exit(1);
      }

      /* if we can safely open the path
       * aka the now current working directory 
       */
      if( ((d = opendir(".")) != NULL) ) {

         /* read entries until end of directory */
         while ((entry = readdir(d)) != NULL) {

               /* debug prints */
               /**/ if ( getcwd(cwd, sizeof(cwd)) == NULL ) {
                  perror("getcwd");
               }
               printf("curr dir = %s\n", cwd);
               /**/
               /* printf("%s\n", entry->d_name); */

               /* make sure entry is not the dot directories */
               if ( !strcmp(entry->d_name, ".") || 
                    !strcmp(entry->d_name, "..") 
               ) {
                  /* printf("ignore . or ..\n"); */
                  continue; 
               }

               /* catch lstat error on a d_name???? */
               if ( lstat( entry->d_name , &sb) == -1 ) {
                  if (!strcmp(path, "..")) {
                     perror(LSTAT_ERROR);
                  }
                  else {
                     /* some other lstat error */
                     perror(path);
                  }
                  exit(1);
               }

               /* if entry is a dir, not leaf */ 
               if ( S_ISDIR( sb.st_mode ) ) {
                  printf("not leaf\n");
                  return 0;
               }
         }

         /* must closedir because opendir */
         closedir(d);
         /* return true */
         return 1;
   }
   printf("fail\n");
   /* return false */
   return 0;
}

int main(int argc, const char *argv[]) {

   if (argc < 2) {
      printf("you suck, gimme 2 args!\n");
      exit(0);
   }

   printf("IS LEAF DIR ??? %d\n", is_leaf_directory(argv[1]));

   return 0;
}
