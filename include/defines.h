#ifndef DEFINES_H
#define DEFINES_H

    // These are here for debugging and expansion. DO NOT TOUCH THEM UNLESS YOU ARE A MADMAN!

    // #define __DEBUG // (uncomment to unlock macOS-specific memory reading functions i guess)

    // arrays
    #define MAX_ARGV 256
    #define WHICH_MAX_PATH_TOKENS 512 // enough for my Mac, enough for anybody

    // input buffers and strings
    #define CWD_SIZE 512 
    #define INPUT_BUF_SIZE 4096 // more than enough
    #define WHICH_PATH_STRING_SIZE 4096

    // COMMANDS
    #define SAFE_EXIT -2

#endif