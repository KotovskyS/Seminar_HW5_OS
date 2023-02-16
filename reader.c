#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int input_fd, output_fd;
    char input_buffer[MAX_BUFFER_SIZE], output_buffer[MAX_BUFFER_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input pipe> <output pipe>\n", argv[0]);
        return 1;
    }

    input_fd = open(argv[1], O_RDONLY);
    output_fd = open(argv[2], O_WRONLY);

    while (1) {
        read(input_fd, input_buffer, MAX_BUFFER_SIZE);
        printf("Received: %s", input_buffer);
        printf("Enter a message: ");
        fflush(stdout);
        fgets(output_buffer, MAX_BUFFER_SIZE, stdin);
        write(output_fd, output_buffer, strlen(output_buffer) + 1);
    }

    return 0;
}

