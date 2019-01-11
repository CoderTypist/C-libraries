#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cjbstring.h"
#include "cjbfile.h"

/* Written by Christian Bargraser October 2018 */

// returns a String containing all the characters leading up to '\n'
// returns NULL if the first character encountered is EOF
// if the first character encountered is '\n', a
// String containing '\0' is returned
char* getLine(FILE *file){
    
    if(NULL == file){
        printf("\n\n\tError: getLine: received file was NULL\n\n");
        return NULL;
    }
    
    // checks to see if the file is at EOF
    char first;
    first = getc(file);
    if(EOF == first){
        return NULL;
    }

    else{
        ungetc(first, file);
    }

    char *line = NULL;
    char cur;
    int length = 0;
    long marker = -1;

    marker = ftell(file);
    
    // creates a string from the individual line
    // length will count the newline character
    // this extra 1 will be used to store the '\0' character
    do{
        
        cur = getc(file);
        length++;
        
        if(cur == EOF){
            
            // if getLine is called and the first character read
            // is EOF, length will be 1, in which case, NULL 
            // should be returned
            if(1 == length){
                return NULL;
            }
            
            // length will always be at least 1, so if length is not 1
            // there is text to be returned

            line = (char*)malloc(length*sizeof(char));
            fseek(file, marker, SEEK_SET);
            int i;
            for(i = 0; i < (length-1); i++){
                line[i] = getc(file);
            }

            line[i] = '\0';
            getc(file);

            return line;
        }

        else if('\n' == cur){
            break;
        }

    }while(true);

    line = (char*)malloc(length*sizeof(char));

    fseek(file, marker, SEEK_SET);
    
    // length will always be at least 1
    // this is in the event that the next character
    // was '\n' or EOF
    int i;
    for(i = 0; i < (length-1); i++){
        line[i] = getc(file);
    }
    line[i] = '\0';

    return line;
}

// prints all the contents  of the received File
// Calls: getLine()
void printFile(FILE *file){
    
    long marker = ftell(file);
    
    char *line = getLine(file);

    while(NULL != line){
        printf("%s\n", line);
        line = getLine(file);
    }

    fseek(file, marker, SEEK_SET);
}

char GetRealC(FILE *fPointer){
    
    char c = getc(fPointer);
    
    if(EOF == c){
        return c;
    }

    while('\n' == c){
        c = getc(fPointer);

        if(EOF == c){
            return c;
        }
    }

    return c;
}

// gets the next character in the file
// Calls: GetRealC
char SeeNextChar(FILE *fPointer){
    // gets the next character
    char next = getc(fPointer);
    // puts that character back
    ungetc(next, fPointer);
    return next;
}

// It is possible that a file will have multiple '\n' characters in a row
// So a call to GetRealC followed by an unget(c) would not work properly
// To work around this, you simply bookmark the the location you are at
// And then go back to that bookmark once you call GetRealC
// Calls: GoTo
char SeeNextRealC(FILE *fPointer){
    
    long marker = ftell(fPointer);
    char c = GetRealC(fPointer);
    GoTo(fPointer, marker);
    return c;

}

// returns a string with the number of requested letters
// if the first character is EOF, NULL is returned
// if the first character is not EOF and EOF is reached,
// the partial String is returned
// You may want to check the length of the returned String in the 
// calling function
char* SeeNextLetters(FILE *fPointer, int numLetters){
    
    // marks the starting location
    long start = ftell(fPointer);
    
    // creates the String
    char* next = NULL;
    char c;
    
    int i;
    for(i = 0; i < numLetters; i++){
        c = GetRealC(fPointer);
        
        if(EOF == c){
            return next;
            // NULL is returnd if the first character is EOF
        }

        else if(0 == i && EOF != c){
            next = AppendChar(next, c);
        }

        else if(i > 0 && EOF != c){
            AppendCharToMallocd(next, c);
        }
    }
    
    // moves to the start location
    GoTo(fPointer, start);

    return next;
}

// goes to the specified location
// this method is meant to safe you the effort of typing out SEEK_SET
int GoTo(FILE *fInput, long marker){
    return fseek(fInput, marker, SEEK_SET);
}

// Returns the number of characters in the specified file
// '\n' and EOF are not counted
// -1 is returned if the received file is NULL
int fileCharacterCount(FILE *file){
    
    if(NULL == file){
        return -1;
    }
    
    int count = 0;
    char *line = getLine(file);
    
    while(NULL != line){
        count+=(int)strlen(line);
        line = getLine(file);
    }
    
    return count;
}

// Moves the file pointer ahead by the specified number of characters
int Advance(FILE *fPointer, int numLetters){
    
    int moved = 0;
    int i;
    char c;

    if(feof(fPointer)){
        return moved;
    }

    for(i = 0; i < numLetters; i++){
        c = getc(fPointer);
        
        moved++;
        if(EOF == c){
            return moved;
        }
    }
    
    return moved;
}

// Moves the file pointer ahead by the specified number of characters
// However, this method calls GetRealC instead of getc
// So the file pointer may actually move ahead more than the
// the specified number of characters
// Calls: GetRealC()
int RealAdvance(FILE *fPointer, int numLetters){
    
    int moved = 0;
    int i;
    char c;

    if(feof(fPointer)){
        return moved;
    }

    for(i = 0; i < numLetters; i++){
        c = GetRealC(fPointer);

        moved++;
        if(EOF == c){
            return moved;
        }
    }

    return moved;
}
