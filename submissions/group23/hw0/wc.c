#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h> // Included for the "isspace" function.

int main(int argc, char* argv[])
{
    unsigned long lineCount = 0, wordCount = 0, characterCount = 0; // Declares counters as unsigned because lack of need for negative values.

    char* currentFile = ""; // Declares the character array to hold the subject file's filename.
    currentFile = argv[1]; // Retrieves the subject file's filename from the argument list.

    FILE* filePointer = NULL; // Declares the file pointer.
    filePointer = fopen(currentFile,"r"); // Opens the subject file as 'read'.

    char character;
    char previous = ' '; // "Previous character" is declared as a space to be able to count the first word.

    characterCount = wordCount = lineCount = 0; // Zeroes-out the counters.
        
    // Loops while current character is not the end of the file.
    while((character = getc(filePointer)) != EOF) {
        characterCount++; // Iterates the character count.

        // Iterates the line count if the current character is a newline.
        if(character == '\n')
            lineCount++; 

        // Iterates the word count if the previous character is a space and the current character is not a space.
        if(isspace(previous) && !isspace(character))
            wordCount++;
        
        previous = character; // Marks current character as the "previous character" to be able to refer to it in the next instance of the loop.
    }
        
    printf("%ld %ld %ld %s\n", lineCount, wordCount, characterCount, currentFile); // Prints out the results.

    return 0;
}