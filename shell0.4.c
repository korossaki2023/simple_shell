#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64
#define ARG_DELIMITER " \t\n\r"
#define PATH_DELIMITER ":"

void handle_exit_command()
{
    exit(EXIT_SUCCESS);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char *args[MAX_ARGS];
    char *path_env = getenv("PATH");

    while (1) {
        printf("$ ");  // Display the prompt
        fflush(stdout);

        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        } else if (bytes_read == 0) {
            // End of file condition (Ctrl+D)
            printf("\n");
            break;
        }

        buffer[bytes_read - 1] = '\0';  // Remove the newline character

        int arg_count = 0;
        char *token = strtok(buffer, ARG_DELIMITER);
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count] = strdup(token);
            token = strtok(NULL, ARG_DELIMITER);
            arg_count++;
        }
        args[arg_count] = NULL;

        // Check if the command is the "exit" built-in
        if (strcmp(args[0], "exit") == 0) {
            handle_exit_command();
        }

        // Check if the command exists in the PATH
        int command_found = 0;
        char *path_token = strtok(path_env, PATH_DELIMITER);
        while (path_token != NULL) {
            char command_path[BUFFER_SIZE];
            snprintf(command_path, BUFFER_SIZE, "%s/%s", path_token, args[0]);
            if (access(command_path, X_OK) == 0) {
                command_found = 1;
                break;
            }
            path_token = strtok(NULL, PATH_DELIMITER);
        }

        if (!command_found) {
            printf("Command not found: %s\n", args[0]);
            continue;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, NULL, 0);
        }

        // Free dynamically allocated memory for arguments
        for (int i = 0; i < arg_count; i++) {
            free(args[i]);
        }
    }

    return 0;
}
