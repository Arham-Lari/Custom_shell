#include "utils.h"
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <cstddef>
#include <cstdio>

Utils *utils = new Utils;

//built in shell command
int cd(char** argv);
int help(char** argv);
int exit(char** argv);

const char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[])(char**) = {
  &cd,
  &help,
  &exit,
};

int num_builtins(){
  return sizeof(builtin_str)/sizeof(char*);
}

int cd(char **argv){
   if(argv[1] == NULL){
     fprintf(stderr, "expected arguument to \"cd\"\n");
   }else{
     if(chdir(argv[0]) != 0){
       perror("lsh");
     }
   }

   return 1;
}

int help(char **argv){
  int i;
  printf("Arham's LSH\n");
  printf("the program names and arguments , and hit enter .\n");
  printf("the following are built in :\n");

  for(i =0 ; i< num_builtins(); i++){
    printf(" %s\n",builtin_str[i]);
  }

  printf("Use the man command for inforamtion on other programs");

  return 1;
}

int exit(char **argv){
  return 0;
}

int execute(char **argv){
  int i;

  if(argv[0] == NULL){
    return 1;
  }

  for (i = 0; i< num_builtins(); i++){
    if(strcmp(argv[0], builtin_str[i]) == 0){
      return (*builtin_func[i])(argv);
    }
  }

  return utils->launch(argv);
}

int main(int argc , char **argv){

    char *line;
    char **args;
    int status;
    do{
        printf("> ");
        line = utils->read_line();
        args = utils->split_line(line);
        status = execute(argv);
    }while(status);

    delete utils;

    return 0;
}
