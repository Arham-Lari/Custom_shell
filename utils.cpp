#include "utils.h"    
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

char* Utils::read_line(){
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

    std::size_t bufsize = TOKEN_SIZE;
    char **tokens = static_cast<char**>(malloc(sizeof(char*)*bufsize));

    char *token;

    if(!tokens){
        fprintf(stderr, "cannot able to allocate memory for tokens\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMA);
    while(token != NULL){
        tokens[position] = token;
        position++;

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
