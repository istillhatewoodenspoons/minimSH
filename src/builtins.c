/* Built-in commands reside here, such as cd, pwd, and exit. */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sorry windows people :P
#include <dirent.h> // for which

#include "builtins.h"
#include "defines.h"
#include "tokenizer.h"

// some builtin commands. currently cd, pwd, and exit.
int checkBuiltin(char** argv) {
    int check = 0;

    if (strcmp(argv[0], "pwd") == 0) {
        char* cwd = malloc(sizeof(char) * CWD_SIZE);

        if (cwd == NULL) {
            perror("pwd: Failed to allocate CWD string memory");
            return -1;
        }

        memset(cwd, 0, CWD_SIZE); // clear the cwd variable to be safe

        if (getcwd(cwd, CWD_SIZE) != NULL) {
            if (argv[1] != NULL) {
                fprintf(stderr, "pwd: no arguments expected\n");
                free(cwd);
                return -1; // --> main(), error, do a continue;
            }
        } else {
            free(cwd);
            perror("pwd"); // print the error message!!!!!!!!!!!!!!!
            return -1;
        }
        printf("%s\n", cwd);
        free(cwd); // free the cwd, memory leak patch
        return 1;
    }

    // exit
    else if (strcmp(argv[0], "exit") == 0) {
        return SAFE_EXIT; // warning to main() that it needs to exit now and must free the argv[] array
    }

    // cd 
    else if (strcmp(argv[0], "cd") == 0) {
        if (argv[1] == NULL) {
            char *homedir = getenv("HOME"); // get home directory
            if (homedir == NULL) {
                perror("cd: failed to get $HOME"); // homedir error
                return -1;
            }

            check = chdir(homedir);

            if (check == 0) {
                return 1; // success           
            } else {
                perror("cd");
                return -1; // error
            }
            // removed unneeded free(), getenv() memory is managed by OS
        }
        
        if (chdir(argv[1]) == 0) {
            return 1; // succesful
        } else {
            perror("cd");
            return -1; // error...
        }
    }

    // clear (removed conditional code, literally all *nixes basically support this shit)
    else if (strcmp(argv[0], "clear") == 0) {
        printf("\033[H\033[2J"); // ansi escape for clearing
        return 1; // success! back to main
    }

    return 0; // if nothing happened
}