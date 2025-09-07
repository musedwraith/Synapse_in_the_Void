// C standard library headers for basic functionality

// can get printf and fgets
#include <stdio.h>
// uses malloc
#include <stdlib.h>
// changes strings
#include <string.h>

#include <errno.h>

// can't use MAX_NAME_LENGTH for BUFFER SIZE
//#define BUFFER_SIZE 16
#define MAX_CHARACTERS 99
#define MAX_BUFFER_SIZE (MAX_CHARACTERS +2)

// constants are fixed values. a character name can only be 100 characters
#define MAX_NAME_LENGTH 100

// define how many characters are held before more memory is needed
#define INITIAL_CAPACITY 10

// defines the data type I have called "character" which points to an array
typedef struct {
    char name[MAX_NAME_LENGTH];
} Character;

void clear_input_stream(FILE *stream){
    int c;
    while ((c = fgetc(stream)) != '\n' && c != EOF);
}

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
    char buffer[MAX_BUFFER_SIZE];

    // same line from the "hello world"
    printf("YOU ARE SO ADORABLE.\n");
    printf("Welcome to Synapse in the Void.\n");
    // /n means new line
    printf("Enter character names (type 'done' to finish):\n");

    // this is the main loop that runs forever unless it is broken out of
    // this loop asks the user to input a name, stores the name, and breaks out of the loop when the user types "done" or if fget fails
    while(1){
        // enter the character's name
        printf("Character %d: ", count + 1);

        // reads text from the user into the buffer
        // reads up to MAX_BUFFER_SIZE - 1
        // if fgets fails, it returns null
        if(fgets(buffer, MAX_BUFFER_SIZE, stdin) == NULL){
            break;
        }

        // serachers for a newline character in the buffer
        char* newL = strchr(buffer, '\n');
        // if no newline is found, and the input was too long to fit into the buffer
        // clear the stream
        if (newL == NULL){
            printf("input is too long. the max is %d characters. skipping this entry.\n\n", MAX_CHARACTERS);
            clear_input_stream(stdin);
            continue;
        }

        // newline = null terminator
        *newL = '\0';

        // stop asking for input when the user types done
        // break the loop and exit
        if (strcmp(buffer, "done") == 0){
            break;
        }

        // check if the arry is full
        if (count >= capacity) {
            // double the capacity
            capacity *= 2;
            // resize the array
            Character* temp = realloc(characters, capacity *sizeof(Character));
            // check for allocation failure
            // if realloc failes, it returns null, and the old memory is untouched
            if (temp == NULL){
                printf("error: could not reallocate memory.\n");
                free(characters);
                return 1;
            }
            // update the pointer
            characters = temp;
        }

        // copy the user's input string from the buffer into the struct of the character's name
        // MAX_NAME_LENGHT - 1 is to leave room for hte null termintor
        // manually add the null termintor to guarentee null termination
        strncpy(characters[count].name, buffer, MAX_NAME_LENGTH - 1);
        characters[count].name[MAX_NAME_LENGTH - 1] = '\0';
        // increase the count
        count++;
    }

    // list the characters entered by the user
    printf("\nCharacters entered:\n");
    // loops through the characters entered by the user 
    // count holds the number
    // print their names
    for (int i = 0; i < count; i++) {
        printf("~ %s\n", characters[i].name);
        //free(characters[i].name);
    }

    // free the entire characters array
    // I have to free it here because I used it in Character* characters = malloc
    free(characters);

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