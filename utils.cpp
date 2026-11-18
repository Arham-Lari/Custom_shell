#include "utils.h"    
#include <cstddef>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>

char* Utils::read_line(void){
    #define size_buffer 1024 

    //to store the buffer size
    std::size_t bufferSize = size_buffer;   

    //to store the position where we are reading right now
    int position = 0;

    //to allocate the memory dynamically
    char *buffer  = static_cast<char*>(malloc(sizeof(char)*bufferSize));
    int c;

    if(!buffer){
        fprintf(stderr, "allocation error in the memory\n");
        exit(EXIT_FAILURE);
    }

    //to read the each char in string
    while(1){

        //to get each char speratly
        c = getchar();

        //to check if there is a space in between the line
        if(c == EOF || c == '\n'){

            //if space is found then make after that make a new line
            buffer[position] = '\0';

            //return the modified buffer
            return buffer;

        }else{

            //if no space is found so add it to the buffer 
            buffer[position] = static_cast<char>(c);
        }
        position++;

        //to check if the position is greater than the buffersize
        if(position >= bufferSize){
            bufferSize += size_buffer;

            //to rellocate the memory if the buffer is full
            buffer = static_cast<char*>(realloc(buffer, bufferSize));

            //to check if the memory is relocated successfully or not
            if(!buffer){
                fprintf(stderr, "unable to rellocate the memory\n");
                exit(EXIT_FAILURE);
            }
        }

        
    }


}

char** Utils::split_line(char *line){
#define TOKEN_SIZE 64
#define TOKEN_DELIMA " \t\r\n\a"

    std::size_t position = 0;

    //initize the buffer the size
    std::size_t bufsize = TOKEN_SIZE;

    //assinging the memory storage for the tokens
    char **tokens = static_cast<char**>(malloc(sizeof(char*)*bufsize));

    //to store each world 
    char *token;

    //checking if memory is successfully allocated
    if(!tokens){
        fprintf(stderr, "cannot able to allocate memory for tokens\n");
        exit(EXIT_FAILURE);
    }

    //it store the pointer of the start of the word
    token = strtok(line, TOKEN_DELIMA);
    while(token != NULL){
        tokens[position] = token;
        position++;

        //assinging the more memory for the token as the space run out
        if(position >= bufsize){
            bufsize += TOKEN_SIZE;
            tokens = static_cast<char**>(realloc(tokens, bufsize));

            if(!tokens){
                fprintf(stderr, "cannot able to increase the memory for the token \n");
                exit(EXIT_FAILURE);
            }
        }
    }

    tokens[position] = NULL;
    return tokens;

}

int Utils::execute(char **args){
 
    pid_t pid , wid;
    int status;

    pid = fork();

    if(pid == 0){

        if(execvp(args[0], args) == -1){
            perror("error");
        }
        exit(EXIT_FAILURE);

    }else if(pid < 0){
        perror("error");
    }else{
        do{

            wid = waitpid(pid,&status,WUNTRACED);

        }while(!WIFEXITED(status));
    }

    return 1;

}
