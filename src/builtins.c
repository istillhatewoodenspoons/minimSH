/* Built-in commands reside here, such as cd, pwd, and exit. */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sorry windows people :P
#include <dirent.h> // for 'which'

#include "builtins.h"
#include "defines.h"
#include "tokenizer.h"

// 'which' is seperate to reduce the already high amount of clutter in checkBuiltin().
int which(char* files[]) {
    char* PATH = NULL; // null string pointer

    // Stage 1: Getting the path
    PATH = getenv("PATH"); // uses malloc() so I'll free it later
    if (PATH == NULL) {
        perror("minimSH: Failed to get $PATH");
        return -1;
    }
}

// some builtin commands. currently cd, pwd, and exit.
int checkBuiltin(char* argv[MAX_ARGV], int which) {
    char* homeDirectory = NULL; // for cd with no arguments

    #if CWD_SIZE <= 2048
        char cwd[CWD_SIZE];
        memset(cwd, 0, CWD_SIZE); // cwd is zeroed out
    #else
        char* cwd = malloc(CWD_SIZE);
        if (cwd == NULL) {
            perror("Failed to allocate CWD string memory");
            return;
        }
        memset(cwd, 0, CWD_SIZE); // fuck you VSC for not syntax highlighting this
    #endif

    // CORE CODE HERE!

    // exit
    if (strcmp(argv[0], "exit") == 0) {
        return -2; // warning to main() that it needs to exit now and must free the argv[] array
    }

    // cd 
    else if (strcmp(argv[0], "cd") == 0) {
        // argument not specified
        if (argv[1] == NULL) {
            homeDirectory = getenv("HOME"); // get the home thingy. I assume getenv uses malloc(), similar to strdup
            if (homeDirectory == NULL) {
                perror("minimSH: Failed to get home directory");
                return -1; // error. Yes, I swear these will get put into some log and won't become useless later on.
            } else {
                // just self-explanatory
                if (chdir(homeDirectory) == 0) {
                    return -1;
                } else {
                    perror("cd");
                    return -1;
                }
            }
        }

        // if an argument is specified
        if (chdir(argv[1]) == 0) {
            return 1; // succesful
        } else {
            perror("cd");
            return -1; // error...
        }
    }

    // pwd
    else if (strcmp(argv[0], "pwd") == 0) {
        // chars shoud usually be bytes, but this may be a dumb decision if some stupid compiler comes along.
        if (getcwd(cwd, CWD_SIZE) != 0) {
            if (argv[1] != NULL) {
                fprintf(stderr, "pwd: no arguments expected\n");
                return -1; // --> main(), error, do a continue;
            }
        } else {
            perror("pwd"); // print the error message!!!!!!!!!!!!!!!
            return -1;
        }
    }

    // clear
    else if (strcmp(argv[0], "clear") == 0) {
        char* term = NULL; // only used in clear
        term = getenv("TERM");
        // very cool comparison
        if ((term != NULL) && (strcmp(term, "xterm") == 0 || strcmp(term, "xterm-256color") || isatty(STDOUT_FILENO))) {
            printf("\033[H\033[2J"); // ansi escape for clearing
            return 1; // success! back to main
        } else if (term == NULL) {
            perror("minimSH"); // haha my shell did the error not getenv
            return -1;
        }
    }

    else if (strcmp(argv[0], "which") == 0) {
        
    }    
    // end of core code

    #if CWD_SIZE > 2048
        free(cwd); // the constant reallocating and deallocating will piss people off, that's for sure.
    #endif

    return 0; // if nothing happened
}