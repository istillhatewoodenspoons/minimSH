#ifndef TOKENIZER_H
#define TOKENIZER_H
    // its own include section
    #include <stdbool.h>
    #include "defines.h"

    typedef struct {
        char* token; // the string part of the token
        bool quotedToken; // did it use a quote (will be expanded later)
        bool redirectionToken; // redirection token? just read the char* if its a redirection token
    } Token;

    // function declerations
    int tokenizer(char* input, char** tokens, const char* delim);
#endif