#include "utils.h"    
#include <cstddef>
#include <cstdio>
#include <cstdlib>

char* Utils::read_line(){
    //to store the buffer size
    std::size_t bufferSize = 1024;   

   //to store the position where we are reading right now
   int position = 0;

   //to allocate the memory dynamically
   char *buffer  = (char*)malloc(sizeof(char)*bufferSize);
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
           buffer[position] = c;
       }
       position++;

      //to check if the position is greater than the buffersize
      if(position >= bufferSize){
          bufferSize += bufferSize;
          buffer = (char*)realloc(buffer, bufferSize);
          //to check if the memory is relocated successfully or not
          if(!buffer){
              fprintf(stderr, "unable to rellocate the memory\n");
              exit(EXIT_FAILURE);
          }
      }
   }


}
