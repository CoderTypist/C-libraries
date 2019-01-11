#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cjbbyte.h"
#include "cjbfile.h"

/* Prints the contents of the received File
 * UTF8 characters are omitted
 */
void printFileOmitUTF8(FILE *file){
    
    long marker = ftell(file);
    
    char *line = getLine(file);
    
    char c;
    int bit;
    int length;
    int i;
    
    while(NULL != line){
        
        length = (int)strlen(line);
        
        for(i = 0; i < length; i++){
            
            c = line[i];
            
            // if the first bit is a 1
            if(1 == bitFromChar(c, 0)){
                continue;
            }
            
            // if the first bit is a 0
            else{
                printf("%c", c);
            }
        }
        
        printf("\n");
        line = getLine(file);
    }

    fseek(file, marker, SEEK_SET);
}

/* Prints the contents of the received File
 * If a the first bit in a byte is 1, all of the bits leading up to the first 0
 * in the byte are printed within "<>"
 * Ex: "<11110>"
 */
void printFileIndicateUTF8(FILE *file){
    
    long marker = ftell(file);
    
    char *line = getLine(file);
    
    char c;
    int bit;
    int length;
    int i;
    
    while(NULL != line){
        
        length = (int)strlen(line);
        
        for(i = 0; i < length; i++){
            
            c = line[i];
            
            // if the first bit is a 1
            if(1 == bitFromChar(c, 0)){
                
                // if the second bit is a 1
                if(1 == bitFromChar(c, 1)){
                    
                    // if the third bit is a 1
                    if(1 == bitFromChar(c, 2)){
                        
                        // if the fourth bit is a 1
                        // the first five bits should never all be 1's
                        if(1 == bitFromChar(c, 3)){
                            printf("<11110>");
                        }
                        
                        // if only the first three bits are 1's
                        else{
                            printf("<1110>");
                        }
                    }
                    
                    // if only the first two bits are 1's
                    else{
                        printf("<110>");
                    }
                }
                
                // if only the first bit is a 1
                else{
                    printf("<10>");
                }
            }
            
            // if the first bit is a 0
            else{
                printf("%c", c);
            }
        }
        
        printf("\n");
        line = getLine(file);
    }

    fseek(file, marker, SEEK_SET);
}

/* Prints the contents of the received File
 * If a byte starts with 1, all of the bits within the
 * bytes are printed within "<>"
 * Example: <11110000>
 */
void printFileRevealUTF8(FILE *file){
    
    long marker = ftell(file);
    
    char *line = getLine(file);
    
    char c;
    int bit;
    int length;
    int i;
    
    while(NULL != line){
        
        length = (int)strlen(line);
        
        for(i = 0; i < length; i++){
            
            c = line[i];
            
            // if the first bit is a 1
            if(1 == bitFromChar(c, 0)){
                
                printf("<");
                printCharBits(c);
                printf(">");
            }
            
            // if the first bit is a 0
            else{
                printf("%c", c);
            }
        }
        
        printf("\n");
        line = getLine(file);
    }

    fseek(file, marker, SEEK_SET);
}

/* Returns the actual character count for a UTF8 encoded String
 */
int trueLineCharacterCountUTF8(char *line){
    
    if(NULL == line){
        return -1;
    }
    
    int length = (int)strlen(line);
    int count = 0;
    char c;
    int i;
    
    for(i = 0; i < length; i++){
            
        c = line[i];
            
        // if the first bit is a 1
        if(1 == bitFromChar(c, 0)){
                
            // if the second bit is a 1
            if(1 == bitFromChar(c, 1)){
                    
                // if the third bit is a 1
                if(1 == bitFromChar(c, 2)){
                        
                    // if the fourth bit is a 1
                    // the first five bits should never all be 1's
                    if(1 == bitFromChar(c, 3)){
                        i+=3;
                        count++;
                        continue;
                    }
                        
                    // if only the first three bits are 1's
                    else{
                        i+=2;
                        count++;
                        continue;
                    }
                }
                    
                // if only the first two bits are 1's
                else{
                    i++;
                    count++;
                    continue;
                }
            }
                
            // if only the first bit is a 1
            else{
                count++;
            }
        }
            
        // if the first bit is a 0
        else{
            count++;
        }
    }
    
    return count;
}

/* Returns the actual character count for a UTF8 encoded File
 */
int trueFileCharacterCountUTF8(FILE *file){
    
    long marker = ftell(file);
    
    if(NULL == file){
        return -1;
    }
    
    int count = 0;
    char *line = getLine(file);
    int i;
    
    while(NULL != line){
        
        count+= trueLineCharacterCountUTF8(line);
        line = getLine(file);
    }
    
    fseek(file, marker, SEEK_SET);
    
    return count;
}
