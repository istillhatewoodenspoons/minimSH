#ifndef DEFINES_H
#define DEFINES_H

    // These are here for debugging and expansion. DO NOT TOUCH THEM UNLESS YOU ARE A MADMAN!
    #define MAX_ARGV 64
    #define MAX_TOKENS 63 // like this because argv array MUST END with NULL

    #define CWD_SIZE 2048 // do not touch this one and make it go over 2048 if you want memory leaks.
    #define INPUT_BUF_SIZE 8192 // more than enough

    // COMMANDS

    #define SAFE_EXIT -2

#endif