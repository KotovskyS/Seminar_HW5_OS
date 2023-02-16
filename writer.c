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

    mkfifo(argv[1], 0666);
    mkfifo(argv[2], 0666);

    printf("Waiting for a reader...\n");

    output_fd = open(argv[1], O_WRONLY);
    input_fd = open(argv[2], O_RDONLY);

    printf("Reader connected. Start typing...\n");

    while (1) {
        printf("Enter a message: ");
        fflush(stdout);
        fgets(input_buffer, MAX_BUFFER_SIZE, stdin);
        write(output_fd, input_buffer, strlen(input_buffer) + 1);
        read(input_fd, output_buffer, MAX_BUFFER_SIZE);
        printf("Received: %s", output_buffer);
    }

    return 0;
}
