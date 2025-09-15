#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relationships.h"

// add relationship

void add_relationship(Relationship** relationships, int* rel_count, int* rel_capacity) {
    // large enough to hold "from to label"
    char buffer[512];

    printf("\nEnter relationship types between characters.\n");
    printf("Enter relationship in format <from> <to> <label>\n");
    printf("Example: Connor Liz engaged\n");
    printf("Example: Connor Liz adoration (thinks she's sweet and cute)\n");
    printf("Type 'done' to finish.\n");

    // reads text from the user into the buffer
    // reads up to MAX_BUFFER_SIZE - 1
    // if fgets fails, it returns null
    if (!fgets(buffer, sizeof(buffer), stdin)) return;

    // finds the newL character and replaces it with \0
    char* newL = strchr(buffer, '\n');
    if (newL) *newL = '\0';

    // checks for done
    if (strcmp(buffer, "done") == 0) {
        printf("Cancelled.\n");
        return;
    }

    Relationship r;
    // r.from = first word = source character
    // r.to = second word = target character
    // r.label = everything else = the description of the relationship
    if (sscanf(buffer, "%s %s %[^\n]", r.from, r.to, r.label) < 3) {
        printf("WRONG INPUT. Format is: charcter name the relationship link is <from> charcter name the relationship link is to <to> type of relationship <label>\n");
        return;
    }

    // check for duplicate relationships
    // this has to be put here because it has to be under where r. is defined
    // == 0 is a boolean
    // && true && true && true
    // check for duplicates
    for (int i = 0; i < *rel_count; i++) {
        if (strcmp((*relationships)[i].from, r.from) == 0 &&
            strcmp((*relationships)[i].to, r.to) == 0 &&
            strcmp((*relationships)[i].label, r.label) == 0) {
            printf("OH NO! Relationship '%s -> %s : %s' already exists. Skipping this entry.\n", 
                   r.from, r.to, r.label);
            return;
        }
    }

    // realloc logic for relationships
    // scales, memory grows dynamically as the user keeps adding relationships
    if (*rel_count >= *rel_capacity) {
        *rel_capacity *= 2;
        Relationship* temp = realloc(*relationships, (*rel_capacity) * sizeof(Relationship));
        if (!temp) {
            printf("ERROR: realloc failed for relationships.\n");
            return;
        }
        *relationships = temp;
    }

    (*relationships)[*rel_count] = r;
    (*rel_count)++;
    printf("Relationship added: %s -> %s : %s\n", r.from, r.to, r.label);
}

void list_relationships(Relationship* relationships, int rel_count) {
    if (rel_count == 0) {
        printf("No relationships yet.\n");
        return;
    }
    printf("=====> weaving connections <=====\n");
    // prints the relationships entered by the user
    for (int i = 0; i < rel_count; i++) {
        printf("%d. %s -> %s : %s\n", i + 1,
               relationships[i].from,
               relationships[i].to,
               relationships[i].label);
    }
}
