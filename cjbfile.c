#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cjbstring.h"
#include "cjbfile.h"

/* Written by Christian Bargraser October 2018 */

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
int GoTo(FILE *fInput, int marker){
    return fseek(fInput, marker, SEEK_SET);
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
