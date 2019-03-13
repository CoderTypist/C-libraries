#ifndef _cjbbyte_h_
#define _cjbbyte_h_

/* Returns the desired bit from the char
 * The char is representative of a byte
 */
int bitFromChar(char c, int index);

/* Prints the bits that make up the char
 */
void printCharBits(char c);

/* returns a char* that has the bits in the received char
 */
char* getCharBits(char c)

/* Prints all of the bits that make up a String
 * EOF is omitted when printing the bits
 * There is a space between every byte/8 bits
 * Printing continues on a new line after
 * bytesPerLine bytes have been printed
 */
void printStringBits(char *cp, int bytesPerLine);

/* Prints all the bits within the specified number of bytes
 * Example: Can be used to print all of the bits within a struct
 * Printing continues on a new line after
 * bytesPerLine bytes have been printed
 */
void printnbytes(void *vp, int bytes, int bytesPerLine);

/* returns a char* that has the bits in the specified size of memory
 */
char* getnbytes(void *vp, int bytes)

#endif
