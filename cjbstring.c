#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cjbstring.h"

/* Written by Christian Bargraser October 2018 */

// returns a char pointer that stores the received char followed by '\0'
char* CharToString(char c){
    
    // creates a char array
    char temp [2];
    temp[0] = c;
    temp[1] = '\0';
    
    // copies the data from the array to the char pointer
    // you can't just return temp
    // it will tell you that you are returning the address
    // of a local variable
    // so what we do is dynically allocate memory for a String
    // and copy the contents from temp to that String
    char *new = (char*)malloc(2*sizeof(char));

    if(NULL == new){
        printf("\n\n\tWarning: CharToString: Could not allocate memory for character '%c'\n\n", c);
    }

    strcpy(new, temp);

    return new;
}

// Use this method if there exists the possibility of the received String not having
// dynamically allocated memory. 
// If the program explicitly says something like
// char *word = "Hello"
// in the code, calling AppendCharToMallocd would cause the program to crash since
// it would try to realloc memory for word, which it can't, since no memory was
// dynamically allocated for it
// Appends a char to a String
// No errors should arise if original is the address of a char
// strlen returns 1 when given a char
// Calls: CharToString()
char* AppendChar(char *original, char c){
    
    if(NULL == original){
        return CharToString(c);
    }

    // Memory is allocated for a new String
    // Why did I add 2?
    // strlen(original) + 1 for the new character + 1 for the '\0'
    char *new = (char*)malloc( (strlen(original) + 2) * sizeof(char));
    
    // if memory could not be allocated for new
    if(NULL == new){
        printf("\n\n\tWarning: AppendChar(): Could not allocate memory.");
        printf("\n\t\tAttempted to add character '%c' to String %s\n\n", c, original);
    }

    // The original word is copied into new
    strcpy(new, original);

    // c is added to new
    char *letter = CharToString(c);
    strcat(new, letter);
    free(letter);

    // The newly constructured String is returned
    return new;
}

// A more efficient version of AppendChar
// However, it only works if the received char pointer has a previous call to malloc
// If the char pointer does not have a previous call to malloc, the program will crash
// If you are unsure if the char you are adding a char had memory mallocd for it
// Use the AppendChar() method. However, you will have to free memory by yourself.
// This method calls realloc, which should free memory if the old data is moved to 
// a new block
// The received String should be NULL if there are no characters in it
// The received String should not be NULL if it has at least one character
// and ends with '\0'
// Returns 0 if memory was reallocated for the String
// Returns -1 if memory could not be allocated for the String
int AppendCharToMallocd(char *original, char c){
    
    if(NULL == original){
        return -1;
    }

    else{
    
        // hold the address held by original
        char *temp = original;

        // strlen(original) + '\0' + character being added
        original = (char*)realloc(original, strlen(original)+2);

        // if memory could be reallocated for original
        if(NULL == original){
            printf("\n\n\tWarning: AppendCharToMallocd(): Could not allocate memory.");
            printf("\n\t\tAttempted to add character '%c' to String %s\n\n",c, temp);
            return -1;
        }

        char *letter = CharToString(c);
        strcat(original, letter);
        free(letter);
        return 0;
    }
}

// Returns a String that starts from startIndex and ends at endIndex
// The String will include the char at index startIndex
// Unlike in java, the String will include the char at endIndex
// Calls: AppendChar(), AppendCharToMallocd(), CharToString()
char* Substring(char *original, int startIndex, int endIndex){
    
    int oLength = (int)strlen(original);
    
    // if startIndex is less than 0
    if(startIndex < 0){
        printf("\n\n\tError: StringBuilder: Substring: startIndex cannot be less than zero.");
        printf("\n\t\tstartIndex: %d\n\n", startIndex);
        return NULL;
    }

    // if endIndex is less than 0
    if(endIndex < 0){
        printf("\n\n\tError: StringBuilder: Substring: endIndex cannot be less than zero.");
        printf("\n\t\tendIndex: %d\n\n", endIndex);
        return NULL;
    }
    
    // if startIndex is greater than or equal to strlen(original)
    if(startIndex >= oLength){
        printf("\n\n\tError: StringBuilder: Substring: startIndex cannot be greater than or equal to strlen(original)"); 
        printf("\n\t\tstartIndex: %d", startIndex);
        printf("\n\t\tstrlen(original): %d", oLength);
        printf("\n\t\toriginal: %s\n\n", original);
        return NULL;
    }

    // if endIndex is greater than or equal to strlen(original)
    if(endIndex >= oLength){
        printf("\n\n\tError: StringBuilder: Substring: endIndex cannot be greater than or equal to strlen(original)");
        printf("\n\t\tendIndex: %d", endIndex);
        printf("\n\t\tstrlen(original): %d", oLength);
        printf("\n\t\toriginal: %s\n\n", original);
        return NULL;
    }   

    // if startIndex is greater than endIndex
    if(startIndex > endIndex){
        printf("\n\n\tError: StringBuilder: Substring: startIndex cannot be greater than endIndex");
        printf("\n\t\tstartIndex: %d", startIndex);
        printf("\n\t\tendIndex: %d\n\n", endIndex);
        return NULL;
    }

    // if startIndex and endIndex are the same
    if(startIndex == endIndex){
        return CharToString(original[startIndex]);
    }
    
    // you cannot call AppendCharToMallocd when memory has not
    // been dynamically allocated for the String
    char *new = CharToString(original[startIndex]);
    
    // We can now call AppendCharToMallocd since we have dynamically 
    // allocated memory for char *new through the call to CharToString
    int i;
    for(i = (startIndex + 1); i <= endIndex; i++){
        AppendCharToMallocd(new, original[i]);
    }

    return new;
}

// This method should receive the address of a pointer
// This pointer must point to memory that was dynamically allocated
// If the memory was not dynamically allocated, the program will crash
// The pointer is freed
// The pointer is then set to NULL
//     Ex:
//     char *word = AppendChar(word, 'H');
//     AppendCharToMallocd(word, 'i');
//     nfree((void*)&word);
// nfree expects a void pointer, so you have to cast the pointer to a void pointer
// You need to send the address of the pointer so that it can be set to NULL
// The syntax used to call this method is rather complicated
// However, the purpose of this method is to ensure that you both free a pointer
// and set it equal to NULL with one method call. Otherwise, you may free a pointer,
// but forget to set it equal to NULL. Some methods may check to see if the received
// pointer is NULL, if you forget to set the pointer equal to NULL yourself, you
// may run into some errors
void nfree(void **dp){
    free(*dp);
    *dp = NULL; 
}

// The purpose of this method is to save you the effort of having to type cast
// the char pointer to a void pointer in the calling function
// This method does the exact same thing as nfree(), except that it exclusively 
// deals with char **
void StringFree(char **dp){
    free(*dp);
    *dp = NULL;
}
