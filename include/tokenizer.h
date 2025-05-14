#ifndef TOKENIZER_H
#define TOKENIZER_H
    // its own include section
    #include <stdbool.h>
    #include "defines.h"

    // types
    typedef struct {
        char* token; // the string part of the token
        bool quotedToken; // did it use quotes?
    } TOKEN;

    // function declerations
    int tokenizer(char* input, char* tokens[MAX_TOKENS]);
#endif