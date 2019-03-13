#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cjbstring.h"

/* Written by Christian Bargraser October 2018 */

// returns a char pointer that stores the received char followed by '\0'
char* CharToString(char c){
    
    // creates a char array
    char *temp = (char*)malloc(2*sizeof(char));

    if(NULL == temp){
        printf("\n\n\tWarning: CharToString: Could not allocate memory for character '%c'\n\n", c);
    }
    
    temp[0] = c;
    temp[1] = '\0';
    
    return temp;
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
    int oldLen = strlen(original);
    char *temp = (char*)malloc( (oldLen + 2) * sizeof(char));
    
    // if memory could not be allocated for new
    if(NULL == temp){
        printf("\n\n\tWarning: AppendChar(): Could not allocate memory.");
        printf("\n\t\tAttempted to add character '%c' to String %s\n\n", c, original);
    }

    // The original word is copied into new
    strcpy(temp, original);
    temp[oldLen] = c;
    temp[oldLen+1] = '\0';
    // The newly constructured String is returned
    return temp;
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
        int oldLen = strlen(original);
        original = (char*)realloc(original, oldLen+2);

        // if memory could be reallocated for original
        if(NULL == original){
            printf("\n\n\tWarning: AppendCharToMallocd(): Could not allocate memory.");
            printf("\n\t\tAttempted to add character '%c' to String %s\n\n",c, temp);
            return -1;
        }

        original[oldLen] = c;
        original[oldLen+1] = '\0';
        
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

// char *one: The first String that will be added to the return String
// char *two: The second String will will be added to the return String
// If both are NULL, NULL is returned
// If either one or two are NULL, the other is returned
// If both are not NULL, a String containing the concatenated Strings is returned
char* Combine(char* one, char* two){
    
    char* both = NULL;

    // if both are not NULL
    if(NULL != one && NULL != two){
        
        int totalLength = strlen(one) + strlen(two) + 1;
        
        both = (char*)malloc(totalLength*sizeof(char));
        
        if(NULL == both){
            printf("\n\n\tWarning: Combine(): Could not allocate memory\n\n");
            exit(1);
        }
        
        strcat(both, one);
        strcat(both, two);
        return both;
    }

    // if one is NULL
    else if(NULL == one && NULL != two){
    
        both = (char*)malloc((strlen(two)+1)*sizeof(char));
        
        if(NULL == both){
            printf("\n\n\tWarning: Combine(): Could not allocate memory\n\n");
            exit(1);
        }
        
        strcpy(both, two);
        return both;
    }

    // if two is NULL
    else if(NULL != one && NULL == two){
    
        both = (char*)malloc((strlen(one)+1)*sizeof(char));
        if(NULL == both){
            printf("\n\n\tWarning: Combine(): Could not allocate memory\n\n");
            exit(1);
        }
        strcpy(both, one);
        return both;
    }
    
    printf("\n\n\tNote: Combine(): Both char* that were received as parameters are NULL.\n\n");
    return NULL;
}

// Combines the specified number of Strings
// a new char* is created and returned
// va_list lengthList and va_list wordList contain the same data
// va_list lengthList is copied into va_list wordList
// a copy of lengthList is made to make it possible to go through the list twice
char* CombineAll(int numArg, ...){
    
    char* phrase = NULL;
    int totalLength = 1; //1 accounts for the null byte
    
    va_list lengthList;
    va_list wordList;
    va_copy(wordList, lengthList);
    
    // finds the amount of space to allocate
    va_start(lengthList, numArg);
    int i;

    for(i = 0; i < numArg; i++){
        
        char *curWord = va_arg(lengthList, char*);
        
        if(NULL != curWord){
            totalLength += strlen(curWord);
        }
        
        else{
            printf("\n\n\tNote: CombineAll(): va_arg %d was NULL\n\n", i);
        }
    }
    va_end(lengthList);
    
    // allocates memory
    phrase = (char*)malloc(totalLength*sizeof(char));
    
    if(NULL == phrase){
        printf("\n\n\tWarning: CombineAll(): Could not allocate memory.\n\n");
        exit(1);
    }
    
    // adds all of the words to the allocated space
    va_start(wordList, numArg);
    for(i = 0; i < numArg; i++){
      
      char *curWord = va_arg(wordList, char*);
      
      if(NULL != curWord){
          strcat(phrase, curWord);
      }
    }
    va_end(wordList);

    return phrase;
}

// Combines the specified number of Strings
// a new char* is created and returned
// va_list lengthList and va_list wordList contain the same data
// va_list lengthList is copied into va_list wordList
// a copy of lengthList is made to make it possible to go through the list twice
// The received delimiter will be inserted between all of the received words
char* CombineAllDelimited(char delimiter, int numArg, ...){
    
    char* phrase = NULL;
    int totalLength = 1; //1 accounts for the null byte
    int numWords = 0;
    
    va_list lengthList;
    va_list wordList;
    va_copy(wordList, lengthList);
    
    // finds the amount of space to allocate
    va_start(lengthList, numArg);
    int i;
    
    for(i = 0; i < numArg; i++){
        
        printf("i: %d\n", i);
        char *curWord = va_arg(lengthList, char*);
        printf("%s\n", curWord);
        if(NULL != curWord){
            totalLength += strlen(curWord);
            numWords++;
        }
        
        else{
            printf("\n\n\tNote: CombineAll(): va_arg %d was NULL\n\n", i);
        }
    }
    
    // numWords increases by one every time a non-NULL char pointer is found
    // numWords will be used to allocate memory for the specified delimiter
    // you only need numWords-1 delimiters
    // However, if numWords is 0, subtracting 1 would make numWords -1, which
    // would make totalLength incorrect
    if(numWords != 0){
        numWords--;
    }
    totalLength+=numWords;
    
    va_end(lengthList);
    
    // allocates memory
    phrase = (char*)malloc(totalLength*sizeof(char));
    
    if(NULL == phrase){
        printf("\n\n\tWarning: CombineAllDelimited(): Could not allocate memory.\n\n");
        exit(1);
    }
    
    bool firstWord = true;
    char* del = CharToString(delimiter);
    
    // adds all of the words to the allocated space
    va_start(wordList, numArg);
    for(i = 0; i < numArg; i++){
      
      char *curWord = va_arg(wordList, char*);
      
      if(NULL != curWord){
          
          if(true == firstWord){
              firstWord = false;
          }
          
          else{
              strcat(phrase, del);
          }
          
          strcat(phrase, curWord);
      }
    }
    va_end(wordList);
    
    return phrase;
}
