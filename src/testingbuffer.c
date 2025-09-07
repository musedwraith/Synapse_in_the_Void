#include <stdio.h>
#include <string.h>
#include <errno.h>

// demonstrated by leocozzens
// the incorperated into main

// define a buffer length
#define BUFFER_SIZE 3

int main(void) {
    // buffer = BUFFER_SIZE
    char buffer[BUFFER_SIZE];

    // reads a line from the user up to BUFFER_SIZE characters
    // prompt for for input until eof is reached
    // eof would be ctrl+z on windows
    // print the line the user entered + -
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        printf("%s - ", buffer);
    }

    // error is set to ENOMEM
    int error = ENOMEM;

    // if there's an error print the ENOMEM message
    if (error) {
        printf("%s\n", strerror(error));
    }

    // exit successfully
    return 0;
}
