#define _GNU_SOURCE // linux compat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

// This function puts strings into tokens[]. They must be free()d. 

int tokenizer(char* input, char** tokens, const char* delim) {
    Token currentToken = { NULL, false, false };
    int count = 0;

    currentToken.token = strtok(input, delim);
        while (currentToken.token != NULL && count < MAX_ARGV - 1) {
            tokens[count] = strdup(currentToken.token); // duplicate, this makes it so that you need to free it later
            fprintf(stderr, "strdup @ tokenizer.c\n");
            currentToken.token = strtok(NULL, delim); // currently only does this with SPACES. will expand to quotations.
            count++; // increment. this will continue until currentToken == NULL and count > 63
        }
    tokens[count] = NULL;
    return count; // return number of tokens stored?
}