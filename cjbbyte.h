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
char* getnbytes(void *vp, int bytes);

/* memPrint does the same thing as printnbytes, except that it accepts 
 * more parameters. If bool addressColumn is true, the address of the first
 * byte in the printed row will be printed. If bool asBits is true, then 
 * the bits of the bytes will be printed. If bool asBits is false, then the hex
 * value of the byte will be printed.
 */
void memPrint(void *vp, int bytes, int bytesPerLine, bool addressColumn, bool asBits);

/* Calls memPrint. Sends true for bool addressColumn.
 * Sends true for bool asBits to print the bits in the bytes.
 */
void memBits(void *vp, int bytes, int bytesPerLine);

/* Calls memPrint. Sends true for bool addressColumn.
 * Sends false for bool asBits to prints the hex value of the bytes.
 */
void memHex(void *vp, int bytes, int bytesPerLine);

#endif
