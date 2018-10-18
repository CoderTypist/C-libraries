#ifndef _cjbfile_h_
#define _cjbfile_h_

/* Written by Christian Bargraser October 2018 */

/* Returns the next character in the file that is not '\n' */
char GetRealC(FILE *fPointer);

/* Returns the next character in the file
 * The calling function will not perceive any change in the file pointer
 */
char SeeNextChar(FILE *fPointer);

/* Returns the next character in the file that is not '\n
 * The calling function will not perceive any change in the file pointer
 */
char SeeNextRealC(FILE *fPointer);

/* Returns a String that contains the following letters in a file 
 * If EOF is reached before constructing a String of size numLetter,
 * the partial String will be returned. It might be necessary to check
 * the size of the returned String in the calling function
 */
char* SeeNextLetters(FILE *fPointer, int numLetters);

/* Moves the file pointer to the location specified by marker
 * All this method does is call fseek
 */
int GoTo(FILE *fPointer, int marker);

/* Moves the file pointer forward by the specified number of characters */
int Advance(FILE *fPointer, int numLetters);

/* Moves the file pointer forward by the specified number of characters
 * However, '\n' is not counted
 */
int RealAdvance(FILE *fPointer, int numLetters);

#endif
