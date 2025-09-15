#include "utils.h"

// repeatedly calls fgetc(stream), reading from stdin,
// and discards characters until it finds a newline or EOF
void clear_input_stream(FILE *stream) {
    int c;
    while ((c = fgetc(stream)) != '\n' && c != EOF);
}
