// C libraries for basic functionality

// can get printf and fgets
#include <stdio.h>
// uses malloc
#include <stdlib.h>
// changes strings
#include <string.h>

// constants are fixed values. a character naame can only be 100 characters
#define MAX_NAME_LENGTH 100

// define how many characters are held before more memory is needed
#define INITIAL_CAPACITY 10

// defines the data type I have called "character" which points to an array
typedef struct {
    char* name;
} Character;

int main(void) {
    // need memory for the characters, use malloc
    Character* characters = malloc(INITIAL_CAPACITY * sizeof(Character));

    // what happens if we can't find the memory
    // error handling is the most overlooked when making simple programs
    // \ means escape sequence
    // return 1 means it failed
    // return 0 would mean success
    if (characters == NULL) {
        printf("Error: could not allocate memory.\n");
        return 1;
    }

    // start the count for how many characters the user has entered at 0
    int count = 0;
    // set the space to the space referred to when determining the space for the characters
    int capacity = INITIAL_CAPACITY;
    // buffer means temporary storage
    char buffer[MAX_NAME_LENGTH];

    // same line from the "hello world"
    printf("YOU ARE SO ADORABLE.\n");
    // /n means new line
    printf("Enter character names (type 'done' to finish):\n");

    // this is the main loop that runs forever unless it is broken out of
    // this loop asks the user to input a name, stores the name, and breaks out of the loop when the user types "done" or if fget fails
    while(1){
        // enter the character's name
        printf("Character %d: ", count + 1);

        // use fget to read the input text and save it in buffer
        // stdin means standared input, stdout means standard output
        // take the user input information, store it in MAX_NAME_LENGTH
        // but if fget fails, break the loop and exit
        if(fgets(buffer, MAX_NAME_LENGTH, stdin) == NULL){
            break;
        }

        //remove the new line of \n 
        buffer[strcspn(buffer, "\n")] = '\0';

        // stop asking for input when the user types done
        // break the loop and exit
        if (strcmp(buffer, "done") == NULL){
            break;
        }

        // memory alloction is important
        // check if more memory is needed to store more characters
        // double the capacity
        // realoc will resize the memory block we already had
        // error code
        if (count >= capacity) {
            capacity *= 2;
            characters = realloc(characters, capacity *sizeof(Character));
            if (characters == NULL){
                printf("Error: could not reallocate memory.\n");
                return 1;
            }
        }

        // allocate memory if needed
        characters[count].name = malloc(strlen(buffer) +1);
        if (characters[count].name == NULL){
            printf("Error: could not allocate memory.");
            return 1;
        }

        // copy the input buffer into the character name
        strcpy(characters[count].name, buffer);

        // move to the next character slot
        count++;
    }

    // print all character names
    // free the memory of the string of "name"
    printf("\nCharacters entered:\n");
    for (int i = 0; i < count; i++){
        printf("- %s\n", characters[i].name);
        free(characters[i].name);
    }

    //free arrray when done
    free(characters);

    return 0;
}