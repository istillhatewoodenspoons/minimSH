/* This is where the main() function resides. It is just called shell.c because this is a fucking shell. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// linux compat reasons
#include <sys/types.h>
#include <sys/wait.h>

#include "builtins.h"
#include "defines.h"
#include "tokenizer.h"

pid_t prog = 0; // this is a global for good reasons lowkey

int main() {
    // mallocs are used to reduce reliance on the stack here and prevent crashes
    char** argv = malloc(sizeof(char*) * MAX_ARGV); // the argv thing
    if (argv == NULL) {
        perror("Critical; malloc");
        exit(EXIT_FAILURE);
    }
    char* input = malloc(sizeof(char) * INPUT_BUF_SIZE);
    if (input == NULL) {
        perror("Critical; malloc");
        exit(EXIT_FAILURE);
    }

    int check = 0; // general-purpose int used for strcspn
    int count = 0; // token counter!!!!
    uid_t uid = geteuid();
    char userChar = 0;

    userChar = uid == 0 ? '#': '$'; // set char based upon uid == 0 and uid != 0
    // main loop
    while (1) {
        printf("minimSH - %c ", userChar); // prompt
        fgets(input, INPUT_BUF_SIZE, stdin); // read a string from stdin
        input[strcspn(input, "\n")] = '\0'; // optimization was done here

        count = tokenizer(input, argv, " \n"); // number of succesful tokens (0-indexed)
        argv[count + 1] = NULL; // removed edge case code to increase efficency and reduce binary size by a bit :D
        
        // builtin commands code + a quick memory freer for the argvs
        if (argv[0] != NULL) {
            check = checkBuiltin(argv);
            if (check == SAFE_EXIT) { // exit
                for (int i = 0; i < count; ++i) {
                    if (argv[i] != NULL) {
                        free(argv[i]); // free the pointers from their shackles.
                    }
                }
                exit(EXIT_SUCCESS);
            } else if (check != 0) {
                // any other builtin. error code will not be handled at this time
                continue;
            }
        }

        prog = fork();

        if (prog < 0) {
            perror("Critical; fork() failed");
            continue; // try again
        } else if (prog == 0) {
            // the child process!
            execvp(argv[0], argv); // execvp()
            perror("minimSH");

            // free argv to prevent leak (only on error)
            for (int i = 0; i < MAX_ARGV; ++i) {
                if (argv[i] != NULL) free(argv[i]);
            }

            exit(EXIT_FAILURE); // exit child process
        } else {
            wait(NULL); // wait, ignore return status
            for (int i = 0; i < MAX_ARGV; ++i) {
                if (argv[i] != NULL) free(argv[i]);
            }
            continue;
        }
    }
    return 0; // never reached usually
}