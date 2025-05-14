#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

// This function puts strings into tokens[]. They must be free()d. 
// 
int tokenizer(char* input, char* tokens[MAX_TOKENS]) {
    char* currentToken = NULL;
    int count = 0;

    currentToken = strtok(input, " \n");
        while (currentToken != NULL && count < MAX_TOKENS) {
            tokens[count] = strdup(currentToken); // duplicate, this makes it so that you need to free it later
            currentToken = strtok(NULL, " \n"); // currently only does this with SPACES. will expand to quotations.
            count++; // increment. this will continue until currentToken == NULL and count > 63
        }
        tokens[count] = NULL;
    return count; // return number of tokens stored?
}

/*
Old tokenizer code for reference

int tokenizer(char* input, char* tokens[MAX_TOKENS]) {
    char* currentToken = NULL;
    int count = 0;

    currentToken = strtok(input, " \n");
        while (currentToken != NULL && count < MAX_TOKENS) {
            tokens[count] = strdup(currentToken); // duplicate, this makes it so that you need to free it later
            currentToken = strtok(NULL, " \n"); // currently only does this with SPACES. will expand to quotations.
            count++; // increment. this will continue until currentToken == NULL && count > 63
        }
        tokens[count] = NULL;
    return count; // return number of tokens stored?
}
*/

