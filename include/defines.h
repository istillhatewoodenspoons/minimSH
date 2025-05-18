#ifndef DEFINES_H
#define DEFINES_H

    // These are here for debugging and expansion. DO NOT TOUCH THEM UNLESS YOU ARE A MADMAN!
    #define MAX_ARGV 128
    #define MAX_TOKENS 127 // like this because argv array MUST END with NULL.

    #define CWD_SIZE 2048 // do not touch this one and make it go over 2048 if you want memory leaks.
    #define INPUT_BUF_SIZE 8192 // more than enough
    #define WHICH_PATH_BUF_SIZE 8192 // used for which command

    // tokenizer specifics
    #define WHICH 1 // the mode used by which. simply prevents the usage of the Token struct defined in tokenizer.h.
    #define NORMAL 0 // usual mode used by the shell

#endif