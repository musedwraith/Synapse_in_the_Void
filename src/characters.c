// can get printf and fgets
#include <stdio.h>
// uses malloc
#include <stdlib.h>
#include <string.h>
#include "characters.h"

//add characters
//list characters
//edit characters

// add characters
void add_character(Character** characters, int* count, int* capacity) {
    char buffer[MAX_NAME_SIZE];
    printf("Enter character name OR type cancel to stop: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return;

    char* newL = strchr(buffer, '\n');
    if (newL) *newL = '\0';
    if (strcmp(buffer, "cancel") == 0) {
        printf("Cancelled.\n");
        return;
    }

    // check for duplicates
    for (int i = 0; i < *count; i++) {
        if (strcmp((*characters)[i].name, buffer) == 0) {
            printf("OH NO! Character '%s' already exists.\n", buffer);
            return;
        }
    }

    if (*count >= *capacity) {
        *capacity *= 2;
        Character* temp = realloc(*characters, (*capacity) * sizeof(Character));
        if (!temp) {
            printf("ERROR: realloc failed for characters.\n");
            return;
        }
        *characters = temp;
    }

    // save character
    strncpy((*characters)[*count].name, buffer, MAX_NAME_SIZE - 1);
    (*characters)[*count].name[MAX_NAME_SIZE - 1] = '\0';
    (*count)++;
    printf("Character '%s' has been added!\n", buffer);
}

// list characters logic
void list_characters(Character* characters, int count) {
    if (count == 0) {
        printf("No characters yet.\n");
        return;
    }
    printf("=====> weaving characters <=====\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, characters[i].name);
    }
}

// edit characters
void edit_character(Character* characters, int count) {
    if (count == 0) {
        printf("No characters to edit.\n");
        return;
    }
    char buffer[MAX_NAME_SIZE];
    printf("\nEdit mode started. Select a character number to rename.\n");
    while (1) {
        printf("\nCharacters:\n");
        for (int i = 0; i < count; i++) {
            printf("%d. %s\n", i + 1, characters[i].name);
        }
        printf("Input the number of the character to edit OR input 0 to stop: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        // atoi compares the number input by the user in the string to an integer index in the array
        int choice = atoi(buffer);
        if (choice == 0) break;
        if (choice < 1 || choice > count) {
            printf("WRONG. Try again.\n");
            continue;
        }

        printf("Enter a new name for '%s': ", characters[choice - 1].name);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            char* newL = strchr(buffer, '\n');
            if (newL) *newL = '\0';

            // prevents renaming to the same name
            // or goes back to the menu
            if (strcmp(buffer, characters[choice -1].name) == 0) {
                printf("OH NO! That's the same name. Skipping rename.\n");
                continue;
            }

            // check for duplicates
            int duplicate = 0;
            for (int dup = 0; dup < count; dup++) {
                if (dup != (choice - 1) && strcmp(characters[dup].name, buffer) == 0) {
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate) {
                printf("OH NO! Character '%s' already exists. Skipping rename.\n", buffer);
            } else {
                strncpy(characters[choice - 1].name, buffer, MAX_NAME_SIZE - 1);
                characters[choice - 1].name[MAX_NAME_SIZE - 1] = '\0';
                printf("CHARACTER UPDATED!\n");
            }
        }
    }
}
