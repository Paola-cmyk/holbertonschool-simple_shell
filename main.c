#include "shell.h"

/**
    * main - Entry point of the shell program.
    *
    * Return: Always 0 (Success).
 */

 int main(void)
 {
    char *input;
    char **args;

    while (1)
    {
        prompt();
        input = read_input();
        args = tokenize(input);
        execute(args);

        free(input);
        free(args);
    }
    return (0);
 }