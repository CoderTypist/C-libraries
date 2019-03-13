#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cjbbyte.h"

// returns the specified bit from within the char
//
// The bits for "A" are 0100 0001
// index 0 = 0
// index 1 = 1
// index 2 = 0
// index 3 = 0
// index 4 = 0
// index 5 = 0
// index 6 = 0
// index 7 = 1
//
// Keep in mind that
// (c>>7)&1 = 1
// (c>>6)&1 = 0
// (c>>5)&1 = 0
// (c>>4)&1 = 0
// (c>>3)&1 = 0
// (c>>2)&1 = 0
// (c>>1)&1 = 1
// (c>>0)&1 = 0
//
// Because of this
// int fetch = 7-index
int bitFromChar(char c, int index){
    
    if(index<0 || index>7){
        return -1;
    }

    int fetch = 7-index;

    return (c>>fetch)&1;
}

// Prints all of the bits that make up the char
void printCharBits(char c){
    
    int i;
    for(i = 7; i >= 0; i--){
        
        if(1 == ( (c>>i)&1 ) ){
            printf("1");
        }

        else{
            printf("0");
        }
    }
}

// returns a char* that has the bits in the received char
char* getCharBits(char c){

    char* byte = (char*)malloc(9*sizeof(char));
    
    if(NULL == byte){
        printf("\n\n\tWarning: getCharBits(): Could not allocate memory for char* byte\n\n");
        return NULL;
    }
    
    int i;
    for(i = 7; i >= 0; i--){
        
        if(1 == ( (c>>i)&1 ) ){
            strcat(byte,"1");
        }

        else{
            strcat(byte,"0");
        }
    }
    
    return byte;
}

// Prints all the bits that make up the String
// The bits for '\0' are not printed
// Printing continues on a new line after
// bytesPerLine bytes have been printed
void printStringBits(char *cp, int bytesPerLine){
    
    int i;
    int j;
    int length = strlen(cp);
    char c;

    for(i = 0; i < length; i++){
        
        // may skip a line
        if(0 != i && 0 == i%bytesPerLine){
            printf("\n");
        }
        
        c = cp[i];
        
        // prints all the bits
        for(j = 7; j >= 0; j--){
            
            if(1 == ( (c>>j)&1 ) ){
                printf("1");
            }

            else{
                printf("0");
            }
        }

        // prints a space between bytes
        printf(" ");
    }
    
    printf("\n");
}

// Prints all the bits within the specified number of bytes
// Example: Can be used to print all the bits within a struct
// Printing continues on a new line after
// bytesPerLine bytes have been printed
void printnbytes(void *vp, int bytes, int bytesPerLine){
    
    if(NULL == vp){
        printf("\n\n\tWarning: printnbytes(): void *vp was NULL\n\n");
        return;
    }
    
    int i;
    int j;
    char *byte = (char*)vp;
    unsigned char c;

    for(i = 0; i < bytes; i++){
        
        // do not advance to the next byte during the first iteration
        if(0 != i){
            byte++;

            // may skip a line
            if(0 == i%bytesPerLine){
                printf("\n");
            }
        }
        
        c = byte[0];
        
        // prints all the bits
        for(j = 7; j >= 0; j--){
            
            if(1 == ( (c>>j)&1 ) ){
                printf("1");
            }

            else{
                printf("0");
            }
        }

        // prints a space between bytes
        printf(" ");
    }

    printf("\n");
}

// returns a char* that has the bits in the specified size of memory
// There is no spacing or new line characters
char* getnbytes(void *vp, int bytes){
    
    if(NULL == vp){
        printf("\n\n\tWarning: getnbytes(): void *vp was NULL\n\n");
        return NULL;
    }
    
    char* address = (char*)vp;
    char* binary = (char*)malloc( (bytes*8)*sizeof(char) + 1 );
    
    if(NULL == binary){
        printf("\n\n\tWarning: getnbytes(): Could not allocate memory for char* binary\n\n");
        return NULL;
    }
    
    int i;
    for(i = 0; i < bytes; i++){
        strcat(binary, getCharBits(address[i]));
    }
    
    return binary;
}
