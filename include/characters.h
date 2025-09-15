#ifndef CHARACTERS_H
#define CHARACTERS_H

#define MAX_CHARACTERS 99
#define MAX_NAME_SIZE (MAX_CHARACTERS + 2)

typedef struct {
    char name[MAX_NAME_SIZE];
} Character;

void add_character(Character** characters, int* count, int* capacity);
void list_characters(Character* characters, int count);
void edit_character(Character* characters, int count);

#endif
