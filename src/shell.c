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

// used for debugging memleaks on macos
#if defined (__MACH__) && defined (__DEBUG)
    #include <mach/mach.h>
    struct task_basic_info info;
    mach_msg_type_number_t size = MACH_TASK_BASIC_INFO_COUNT;
    kern_return_t kerr;
#endif

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
        #if defined (__MACH__) && defined (__DEBUG)
            kerr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &size);
            if (kerr == KERN_SUCCESS)
                printf("(memsize - %012llu bytes) minimSH - %c ", (unsigned long long)info.resident_size, userChar); // prompt
            else
                printf("(task_info() failed) minimSH - %c ", userChar);
        #else
            printf("minimSH - %c ", userChar); // prompt
        #endif
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
                        argv[i] = NULL; // prevent dangling pointers
                    }
                }
                free(argv); // failed to put this in here
                free(input); // and this
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
                if (argv[i] != NULL) { 
                    free(argv[i]);
                    argv[i] = NULL; // dangling pointer fix
                }
            }

            exit(EXIT_FAILURE); // exit child process
        } else {
            wait(NULL); // wait, ignore return status
            for (int i = 0; i < MAX_ARGV; ++i) {
                if (argv[i] != NULL) {
                    free(argv[i]);
                    argv[i] = NULL; // dangling pointer fix + satisfy check
                }
            }
            continue;
        }
    }
    // if a catastrophic error does occur, these are a safeguard
    free(argv);
    free(input);
    return 0; // never reached usually
}