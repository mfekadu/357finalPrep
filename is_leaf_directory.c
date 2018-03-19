#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>

int is_leaf_directory(const char *path) {
  struct stat sb;
  struct dirent *entry;
  DIR *dirp;

  /*if path too long*/
  if(strlen(path) > PATH_MAX) {
    printf("path too long\n");
    return 0;
  }

  if( (lstat(path, &sb) != -1) && /*if path exists*/
      /* and not a symlink*/
      (!S_ISLNK(sb.st_mode)) &&             
      /* and is a directory*/
      ((dirp = opendir(path)) != NULL)
   ) {
        /*read entries until end of directory*/
        while((entry = readdir(dirp)) != NULL) {
          if(entry->d_type == DT_DIR) {
            printf("subdirectory\n");
            return 0;
          }
        }
        return 1;
      }
  perror(path);
  return 0;
}




int main(int argc, const char *argv[]) {

   if (argc < 2) {
      perror("you suck");
      exit(0);
   }

   printf("IS LEAF DIR ??? %d\n", is_leaf_directory(argv[1]));

   return 0;
}
