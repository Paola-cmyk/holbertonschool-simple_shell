#include "libraryshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

#define MAX_INPUT 1024
#define PROMPT "$"

/**
 * search_path - Search for the command in PATH directories
 * @command: the command to find
 *
 * Return: full path to the executable if found, else NULL
 */
char *search_path(char *command)
{
    char *path_env = getenv("PATH");
    char *path_copy, *dir, *full_path;
    struct stat st;

    if (!path_env)
        return NULL;

    path_copy = strdup(path_env);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
int main(int argc, char *argv[])
{
    pid_t pid;
    char input[MAX_INPUT];
    char *command_path;

    if (argc > 1)
    {
        strncpy(input, argv[1], MAX_INPUT - 1);
        input[MAX_INPUT - 1] = '\0';
    }

    while (1)
    {
        if (argc == 1)
        {
            printf(PROMPT);
            fflush(stdout);

            if (fgets(input, sizeof(input), stdin) == NULL)
            {
                printf("\n");
                break;
            }

            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) == 0)
                continue;
        }

        if (strcmp(input, "env") == 0)
        {
            for (int i = 0; environ[i] != NULL; i++)
                printf("%s\n", environ[i]);

            if (argc > 1)
                break;
            continue;
        }

        if (input[0] == '/' || input[0] == '.')
        {
            if (access(input, X_OK) == 0)
                command_path = strdup(input);
            else
                command_path = NULL;
        }
        else
        {
            command_path = search_path(input);
        }

        if (!command_path)
        {
            fprintf(stderr, "%s: command not found\n", input);
            if (argc > 1)
                break;
            continue;
        }

        pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            free(command_path);
            continue;
        }

        if (pid == 0)
        {
            char *exec_args[] = { command_path, NULL };
            execve(command_path, exec_args, environ);
            perror("Execution failed");
            free(command_path);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
            free(command_path);
        }

        if (argc > 1)
            break;
    }

    return 0;
}

