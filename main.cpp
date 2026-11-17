#include "utils.h"
#include <cstdio>
int main(int argc , char **argv){

    Utils *utils = new Utils;
    
    char *line;
    char **args;
    int status;
    do{
        printf("> ");
        line = utils->read_line();
        args = utils->split_line(line);
        status = utils->execute(args);
    }while(status);

    delete utils;

    return 0;
}
