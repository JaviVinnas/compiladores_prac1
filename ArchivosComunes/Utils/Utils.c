#include <Utils.h>
#include <stdio.h>
#include <stdlib.h>



void printSeparator(){
    printf("----------------------------------------------------------------");
    printf("\n");
};

char *charToString(char c){
    char *string = malloc(sizeof(char)*2);
    string[0] = c;
    string[1] = '\0';
    return string;
}