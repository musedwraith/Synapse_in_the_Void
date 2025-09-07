// C standard library headers for basic functionality

// can get printf and fgets
#include <stdio.h>
// uses malloc
#include <stdlib.h>
// changes strings
#include <string.h>

// can't use MAX_NAME_LENGTH for BUFFER SIZE
#define BUFFER_SIZE 16

// constants are fixed values. a character name can only be 100 characters
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

        // array that holds a chunk of user input. it doesn't read the full input, it reads in chunks
        char temp[BUFFER_SIZE];
        // points to a character to build the full line from the chunks stored in temp
        char* fullLine = NULL;
        // unassigned integer to keep track of how many characters have accumulated
        size_t fullSize = 0;
        // flag that signals the MAX_NAME_LENGTH has been exceeded
        int inputTooLong = 0;

        // use fget to read the input text and save it in buffer
        // stdin means standared input, stdout means standard output
        // take the user input information, store it in MAX_NAME_LENGTH
        // but if fget fails, break the loop and exit
        // read chunks until there is a newline or eof
        while (1) {
            // read a chunk of input up to the BUFFER_SIZE - 1 characters and place into a temporary array
            // fgets stops reading if it gets to a newline, oef, or fills the buffer
            if(fgets(temp, BUFFER_SIZE, stdin) == NULL){
                break;
            }

            // how many characters are read into the buffer
            // needed to track memory to allocate
            size_t chunkLen = strlen(temp);
            // checks if the last character is a newline 
            int endsWithNewLine = temp[chunkLen -1] == '\n';

            // total size of the accumulated + size of the current chunk >= MAX_NAME_LENGTH
            if (fullSize + chunkLen >= MAX_NAME_LENGTH) {
                // input is too long flag
                inputTooLong = 1;
                // remove the rest of the input from the buffer until the end of the line so the next characters aren't carried over
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                // exit
                break;
            }
            
            // ask for a new block of memory large enough to hold old data + the new chunk + 1 for the null terminator (\0)
            char* newLine = realloc(fullLine, fullSize + chunkLen + 1);
            // if realloc fails, clean it up and exit
            if(!newLine){
                printf("error: can't allocate memory for next line input");
                free(fullLine);
                free(characters);
                return 1;
            }

            // merge input chunks from the old and new data
            fullLine = newLine;
            // copy the enw chunk tot he end of the existing full line
            memcpy(fullLine + fullSize, temp, chunkLen);
            // track how long the line is now
            fullSize += chunkLen;
            // mark the end of the string with the null terminator
            fullLine[fullSize] = '\0';

            // if the user hits enter, the last character is \n, replace it with \0, remove new line, and end the string
            if (endsWithNewLine) {
                fullLine[fullSize -1 ] = '\0';
                break;
            
            }
        }

            // if the chunk ends in a newline, stop reading the line
            //if (temp[chunkLen -1] == '\n') {
                // remove newline
            //    fullLine[fullSize - 1] = '\0';
            //    break;
            //}

        //printf("chunk read: '%s\n", temp);

        //if (strchr(fullLine, '\n') == NULL) {
        //    int ch;
        //    while ((ch = getchar()) != '\n' && ch != EOF);
        //    printf("warning the input was too long.\n", MAX_NAME_LENGTH -1);
        //}

        // THIS LINE DOESN'T RUN. FIX IT.
        // return null asap
        //if (!fullLine) {
        //    if (inputTooLong){
        //        printf("input is too long, skipping this entry.\n\n", MAX_NAME_LENGTH - 1);
        //        continue;
        //    } else {
        //        break;
        //    }
       // }

       // if the input is too long, print an error message
       if (inputTooLong) {
        printf("input is too long (max of %d characters), skipping this entry.\n\n", MAX_NAME_LENGTH - 1);
        // if the input is invalid, the memory may have been allocated to build the part of this string before this point
        // free the memory for the incomplete line
        free(fullLine);
        continue;
        }
    
        // if fullLine is null, there was nothing to store, exit
        if (!fullLine) {
            break;
        }


        //remove the new line of \n 
        //buffer[strcspn(buffer, "\n")] = '\0';

        // stop asking for input when the user types done
        // break the loop and exit
        if (strcmp(fullLine, "done") == 0){
            free(fullLine);
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
                free(fullLine);
                return 1;
            }
        }

        // store the name
        characters[count].name = fullLine;
        count++;

        // allocate memory if needed
        //characters[count].name = malloc(strlen(buffer) +1);
        //if (characters[count].name == NULL){
        //    printf("Error: could not allocate memory.");
        //    return 1;
        //}

        // copy the input buffer into the character name
        //strcpy(characters[count].name, buffer);

        // move to the next character slot
        //count++;
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