#ifndef LIBRARYSHELL_H
#define LIBRARYSHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10

extern char **environ;
char *_getenv(const char *name);
char **parse_input(char *input);
int execute_command(char **args);
int execute_or_find_command(char **args);

#endif /* LIBRARYSHELL_H */
