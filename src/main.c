#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "characters.h"
#include "relationships.h"
#include "utils.h"

// define how many characters are held before more memory is needed
#define INITIAL_CAPACITY 10

#define MAX_CHARACTERS 99

// can't use MAX_NAME_LENGTH for BUFFER SIZE
#define MAX_BUFFER_SIZE (MAX_CHARACTERS + 2)

int main(void) {
    // need memory for the characters and relationships, use malloc
    Character* characters = malloc(INITIAL_CAPACITY * sizeof(Character));
    Relationship* relationships = malloc(INITIAL_CAPACITY * sizeof(Relationship));

    // what happens if we can't find the memory
    // error handling is the most overlooked when making simple programs
    // \ means escape sequence
    // return 1 means it failed
    // return 0 would mean success
    if (characters == NULL || relationships == NULL) {
        printf("ERROR: could not allocate memory.\n");
        return 1;
    }

    // no relationships or characters exist at the start of the program
    // INITIAL_CAPACITY = current array size
    int char_count = 0, char_capacity = INITIAL_CAPACITY;
    int rel_count = 0, rel_capacity = INITIAL_CAPACITY;

    char buffer[MAX_BUFFER_SIZE];

    printf("YOU ARE SO ADORABLE.\n");
    printf("Welcome to Synapse in the Void.\n");
    printf("=====> weaving constellations of a thought <=====\n");
    printf("Type a command. (help for list)\n");

    while (1) {
        printf("\n> ");
        // reads text from the user into the buffer
        // reads up to MAX_BUFFER_SIZE - 1
        // if fgets fails, it returns null
        if (!fgets(buffer, sizeof(buffer), stdin)) break;

        char* newL = strchr(buffer, '\n');
        if (newL) *newL = '\0';

        // menu
        // rel_count relationships
        // char_count characters
        if (strcmp(buffer, "help") == 0) {
            printf("Commands:\n");
            printf("  1. addchar   - Add a new character\n");
            printf("  2. listchar  - List all characters\n");
            printf("  3. editchar  - Edit all characters\n");
            printf("  4. addrel    - Add a new relationship\n");
            printf("  5. listrel   - List all relationships\n");
            printf("  6. clear     - Clear the screen\n");
            printf("  7. quit      - Exit program\n");
        } else if (strcmp(buffer, "1") == 0 || strcmp(buffer, "addchar") == 0) {
            add_character(&characters, &char_count, &char_capacity);
        } else if (strcmp(buffer, "2") == 0 || strcmp(buffer, "listchar") == 0) {
            list_characters(characters, char_count);
        } else if (strcmp(buffer, "3") == 0 || strcmp(buffer, "editchar") == 0) {
            edit_character(characters, char_count);
        } else if (strcmp(buffer, "4") == 0 || strcmp(buffer, "addrel") == 0) {
            add_relationship(&relationships, &rel_count, &rel_capacity);
        } else if (strcmp(buffer, "5") == 0 || strcmp(buffer, "listrel") == 0) {
            list_relationships(relationships, rel_count);
        } else if (strcmp(buffer, "6") == 0 || strcmp(buffer, "clear") == 0) {
            #ifdef _WIN32
            system("cls");
            #else
            system("clear");
            #endif
        } else if (strcmp(buffer, "7") == 0 || strcmp(buffer, "quit") == 0) {
            printf("Goodbye, traveler of the void.\n");
            break;
        } else {
            printf("OH NO! That's an unknown command. Type 'help' for options.\n");
        }
    }

    // free the entire characters and relationships array
    // I have to free it here because I used it in Character* characters = malloc
    free(characters);
    free(relationships);

    // check for errors
    // this is an error while reading the standard input
    // error message I/O = input/output
    if (ferror(stdin)) {
        printf("I/O failed.\n");
        return EIO;
    }

    // successful exit
    return 0;
}
