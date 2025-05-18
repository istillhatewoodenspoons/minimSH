#ifndef TOKENIZER_H
#define TOKENIZER_H
    // its own include section
    #include <stdbool.h>
    #include "defines.h"

    // types
    typedef struct token {
        char* token; // the string part of the token
        // yes i'm wasting a lot of memory here but please cut me some slack
        bool quotedToken;
        bool redirectionToken;
        bool doubleQuotedToken;
    } Token;

    // function declerations
    int tokenizer(char* input, char* tokens[MAX_TOKENS]);
#endif