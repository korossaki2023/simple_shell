#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

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

        int status = system(buffer);
        if (status == -1) {
            perror("system");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
