#include "shell.h"

/**
    * prompt - displays the shell prompt
    */


void prompt(void)
{
write(1, "$ ", 2);
}

/**
 * read_input - reads a line of input from the user
 *
 * Return: pointer to the input string
 */

 char *read_input(void)
 {
     char *input = NULL;
     size_t len = 0;
     ssize_t nread;

     nread = getline(&input, &len, stdin);
     if (nread == -1)
     {
         free(line);
         exit(0);
    }
    return (line);
 }

 /**
    *tokenize - splits the input string into tokens
    * @input: the input string

    * Return: array of tokens
    */

char **tokenize(char *input)
{
    char *token;
    char **tokens = malloc(64 * sizeof(char *));
    int i = 0;

    if (tokens == NULL)
    {
        perror("malloc");
        exit(1);
    }

    token = strtok(input, " \n");
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    tokens[i] = NULL;
    return (tokens);
}

/**
* execute - executes the command
* @args: array of command and arguments
 */

 void execute(char **args)
 {
    pid_t pid;
    int status;

     if (args[0] == NULL)
     {
         return;
     }

     pid = fork();
     if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
        else if (pid == 0)
    }

        if (execvp(args[0], args) == -1)
        {
        perror("execvp");
        }
        exit(EXIT_FAILURE);
    } 
    else
    {
        waitpid(pid, &status, 0);
    } 
}

/**
    * find_command - checks if the command is valid
    * @command: the command to check
    *
    * Return: 1 if valid, 0 if not
 */

 char find_command(char *command)
 {
    char *path = getenv("PATH");
    char *token, *full_path;
    struct stat st;
    size_t len;

    if (!path)
    return (NULL);

    token = strtok(path, ":");
    while (token != NULL)
    {
        len = strlen(token) + strlen(command) + 2;
        full_path = malloc(len);
        if (!full_path)
        {
            perror("malloc");
            return (NULL);
        }
        snprintf(full_path, len, "%s/%s", token, command);
        if (stat(full_path, &st) == 0)
        {
            free(full_path);
            return (1);
        }
        free(full_path);
        token = strtok(NULL, ":");
        }
    }
    return (0);
}