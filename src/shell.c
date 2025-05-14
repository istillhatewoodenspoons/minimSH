/* This is where the main() function resides. It is just called shell.c because this is a fucking shell. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>

#include "builtins.h"
#include "defines.h"
#include "tokenizer.h"

int main() {
    pid_t prog = 0;
    char* argv[MAX_ARGV]; // the argv thing.
    char input[INPUT_BUF_SIZE];

    int check = 0; // general-purpose int used for strcspn
    int count = 0; // token counter!!!!

    // main loop
    while (1) {
        printf("minimSH - %c ", geteuid() == 0 ? '#' : '$'); // show if running as root user or regular user by checking effective user id

        fgets(input, INPUT_BUF_SIZE, stdin); // read a string from stdin
        
        check = strcspn(input, "\n"); // process of removing a newline
        if (check != strlen(input))
            input[check] = '\0'; // set to NULL character

        count = tokenizer(input, argv); // number of succesful tokens (0-indexed)

        // a token limit edge case was removed, it was pretty useless
        argv[count + 1] = NULL; // this should work but the edge case is there for fun and to catch somebody fucking with the code
        
        
        // builtin commands code + a quick memory freer for the argvs
        if (argv[0] != NULL) {
            check = checkBuiltin(argv);
            if (check == -2) {
                for (int i = 0; i < count; ++i) {
                    if (argv[i] != NULL)
                        free(argv[i]); // free the pointers from their shackles.
                }
                exit(EXIT_SUCCESS);
            } else if (check != 0) {
                // -2 will never reach here because it would exit. Just clarifying.
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
            perror("minimSH"); // I BLAME MYSELF (print error)
            exit(EXIT_FAILURE); // exit child process
        } else {
            wait(NULL); // wait, ignore return status
            continue;
        }
    }
    return 0; // the magical code word!
}