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

// defines the maximum length for the string for Relationship
// this is the TYPE of relationship
#define MAX_REL_TYPE_LENGTH 100

// defines the maximum length for the string for details regarding the relationship
// information about the relationship
#define MAX_DETAIL_LENGTH 200

// holds information about a single character - a single node
// defines the data type I have called "character" which points to an array
typedef struct {
    char name[MAX_NAME_LENGTH];
} Character;

// holds information about two characters - the direct edge between 2 nodes
// for the data type Relationship, each Relationship variable will store
// a source character: "from"
// a target character: "to"
// a description of the relationship type: "label"
typedef struct {
    char from[MAX_DETAIL_LENGTH];
    char to[MAX_DETAIL_LENGTH];
    char label[MAX_DETAIL_LENGTH];
} Relationship;

// repeatedly calls fgetc(stream), reading from the stdin, 
// and throws away characters until it finds a newL or reaches the EOF
void clear_input_stream(FILE *stream){
    int c;
    while ((c = fgetc(stream)) != '\n' && c != EOF);
}

int main(void) {
    // need memory for the characters and relationships, use malloc
    Character* characters = malloc(INITIAL_CAPACITY * sizeof(Character));
    Relationship* relationships = malloc(INITIAL_CAPACITY * sizeof(Relationship));

    // what happens if we can't find the memory
    // error handling is the most overlooked when making simple programs
    // \ means escape sequence
    // return 1 means it failed
    // return 0 would mean success
    if (characters == NULL) {
        printf("ERROR: could not allocate memory.\n");
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
    printf("=====> weaving constellations of a thought <=====\n");
    printf("Enter character names:\n");
    printf("Type 'done' to finish.\n");

    // character input while loop
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
            printf("INPUT IS TOO LONG. The max is %d characters. Skipping this entry.\n\n", MAX_CHARACTERS);
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

        //check for duplicates
        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(characters[i].name, buffer) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("OH NO! Character '%s' already exists. Skipping this entry.\n", buffer);
            continue;
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
                printf("ERROR: could not reallocate memory.\n");
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

    printf("=====> weaving characters <=====\n");
    // list the characters entered by the user
    printf("\nCharacters entered:\n");
    // loops through the characters entered by the user 
    // count holds the number
    // print their names
    for (int i = 0; i < count; i++) {
        printf("~ %s\n", characters[i].name);
    }

    printf("\nEdit a character's name? (yes/no): ");
    if (fgets(buffer, MAX_BUFFER_SIZE, stdin)) {
        char* newL = strchr(buffer, '\n');
        if (newL) *newL = '\0';

        if (strcmp(buffer, "yes") == 0) {
            while (1) {
                printf("\nCharacters:\n");
                for( int i = 0; i < count; i++) {
                    printf("%d. %s\n", i + 1, characters[i].name);
                }
                printf("Input the number of the character to edit OR input 0 to stop: ");

                if (!fgets(buffer, MAX_BUFFER_SIZE, stdin)) break;
                // atoi compares the number input by the user in the string to an integer index in the array
                int choice = atoi(buffer);

                if (choice == 0) break;
                if (choice < 1 || choice > count) {
                    printf("WRONG. Try again\n");
                    continue;
                }

                printf("Enter a new name for '%s': ", characters[choice - 1].name);
                if (fgets(buffer, MAX_BUFFER_SIZE, stdin)) {
                    char* newL = strchr(buffer, '\n');
                    if (newL) *newL = '\0';
                    
                    // check for a duplicated before renaming a character
                    int duplicate = 0;
                    for (int rename = 0; rename < count; rename++) {
                        if (rename != (choice - 1) && strcmp(characters[rename].name, buffer) == 0) {
                            duplicate = 1;
                            break;
                        }
                    }

                    if (duplicate) {
                        printf("OH NO! Character '%s' already exists. Skipping rename entry.\n", buffer);
                    } else {
                        if (strncmp(buffer, characters[choice - 1].name, MAX_NAME_LENGTH) == 0) {
                            printf("OH NO! '%s' is taken. Skipping this rename.", buffer);
                        } else {
                            strncpy(characters[choice -1].name, buffer, MAX_NAME_LENGTH - 1);
                            characters[choice - 1].name[MAX_NAME_LENGTH - 1] = '\0';
                            printf("CHARACTER UPDATED!\n");
                        }
                    }
                }
            }
        }
    }


    printf("\nEnter relationship types between characters.\n");
    printf("Enter in the format of: <from> <to> <label>\n");
    printf("Example: Connor Liz engaged\n");
    printf("Example: Connor Liz adoration (thinks she's sweet and cute)\n");
    printf("Type 'done' to finish.\n");

    // no relationships exist at the start of the program
    // INITIAL_CAPACITY = current array size
    int rel_count = 0;
    int rel_capacity = INITIAL_CAPACITY;

    while(1) {
        // lists the relationships by number
        printf("Relationship %d: ", rel_count + 1);
        // reads text from the user into the buffer
        // reads up to MAX_BUFFER_SIZE - 1
        // if fgets fails, it returns null
        if (fgets(buffer, MAX_BUFFER_SIZE, stdin) == NULL) break;
        // finds the newL character and replaces it with \0
        char* newL = strchr(buffer, '\n');
        if (newL) * newL = '\0';
        // checks for done
        if (strcmp(buffer, "done") == 0) break;

        Relationship r;
        // r.from = first word = source character
        // r.to = second word = target character
        // r.label = everything else = the description of the relationship
        if (sscanf(buffer, "%s %s %[^\n]", r.from, r.to, r.label) < 3) {
            printf("WRONG INPUT. Try again.\n");
            continue;
        }

        // realloc logic for relationships
        // scales, memory grows dynamically as the user keeps adding relationships
        if (rel_count >= rel_capacity){
            rel_capacity *= 2;
            Relationship* temp = realloc(relationships, rel_capacity * sizeof(Relationship));
            if (!temp) {
                printf("ERROR: realloc failed for relationships.\n");
                free(relationships);
                free(characters);
                return 1;
            }
            relationships = temp;
        }

        // check for duplicate relationships
        // this has to be put here because it has to be under where r. is defined
        // == 0 is a boolean
        // && true && true && true
        int duplicate = 0;
        for (int i =0; i < rel_count; i++) {
            if (strcmp(relationships[i].from, r.from) == 0 &&
                strcmp(relationships[i].to, r.to) == 0 &&
                strcmp(relationships[i].label, r.label) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("OH NO! Relationship '%s -> %s : %s' already exists. Skipping this entry.\n",
                r.from, r.to, r.label);
                continue;
        }

        // save the relationships
        relationships[rel_count++] = r;
    }

    printf("=====> weaving connections <=====\n");
    printf("\nRelationships entered:\n");
    // prints the relationships entered by the user
    for (int i = 0; i < rel_count; i++) {
        printf("~ %s -> %s : %s\n", 
            relationships[i].from,
            relationships[i].to,
            relationships[i].label);
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