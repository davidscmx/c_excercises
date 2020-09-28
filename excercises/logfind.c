/* Project logfind: Ex. 26 from LCTHW

The purpose of logfind should be similar to that of grep,
but only for logfiles in the system. Usage:
logfind david

This will search all the common places where log files are stores and
print out everyfile that contains the word "david" on it */


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // 
#include <string.h>

// https://stackoverflow.com/questions/8133074/error-unknown-type-name-bool
#include <stdbool.h>  // C90 does not support the boolean data type, C99 does include it with this include

// Code from:
//https://stackoverflow.com/questions/14618008/how-can-i-check-if-file-is-text-ascii-or-binary-in-c
bool is_binary(const void *data, size_t len)
{
    return memchr(data, '\0', len) != NULL;
}



int main(int argc, char *argv[]){

  /*
    Features needed for the program
    -- 
    Display files which contain the words given in the argument 
   */

  // Read and display files in directory
  DIR *dir;
  dir = opendir(".");
  struct dirent *dp;
  
  while ((dp=readdir(dir)) != NULL) {
    printf("file: %s\n", dp->d_name); // print all the files in this directory   
    FILE *fp = fopen(dp->d_name, "r"); // open the file
    
    bool bin_or_not = is_binary(fp,20);
    printf("Is my file a binary file: %d ",bin_or_not);

    if (bin_or_not) continue;

    if (fp == NULL )  
      exit(-1);

    char line[256];

    while (fgets(line, sizeof(line), fp)) {
      /* note that fgets don't strip the terminating \n, checking its
	 presence would allow to handle lines longer that sizeof(line) */
      printf("%s", line); 
    }
    
    //    while ((read = getline(&line, &len, fp)) != -1) {
      //      printf("Retrieved line of length %zu :\n", read);
//      printf("%s", line);
//    }
//     
//    fclose(fp);
//    if (line)
//      free(line);   
  }  
 
  for (int i = 0; i < argc; i++){
    printf("This word %s \n",argv[i]);
  }
  
  return 0;
}
