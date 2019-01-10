#ifndef _cjbUTF8_h_
#define _cjbUTF8_h_

/* This program was inspired from a lecture I watched online by James McNellis
 * The video is engaging and very informative
 * I highly recommend the video for anyone wanted to learn about unicode
 * https://www.youtube.com/watch?v=tOHnXt3Ycfo
 *
 * Some files are uncoded using the UTF8 format
 * Under the UTF8 format, some characters consist of more than 1 byte
 * Characters can use up to 4 bytes
 * If the first bit is 0, then the character only uses 1 byte
 * If the first bits are "11110", then the character consists of 4 bytes
 * If the first bits are "1110", then the character consists of 3 bytes
 * If the first bits are "110", then the character consists of 2 bytes
 * The bytes following bytes that start with "11110", "1110", or "110"
 * are called trail bytes and all start with "10"
 * 
 * When printing a UTF8 encoded file to the console, UTF8 characters may be printed properly,
 * even though they consist of multiple bytes. This program helps visually show how UTF8
 * encoded characters can be consist of multiple bytes.
 *
 * getc() returns a char consisting of the next byte/8 bits in the file
 * If getc() is reading from a UTF8 encoded file, getc() will only return
 * the next byte/8 bits, and remember that many characters in UTF8
 * consist of multiple bytes. If you wanted to count the number of characters
 * in a UTF8 encoded file by using getc(), you would likely receive an incorrect
 * result. getc() goes by byte/8 bits, so if a UTF8 character consists of 4 bytes,
 * the function would count that character as 4 different characters. To avoid this
 * mistake, it is necessary to check the first few bits within the byte and make
 * the appropriate adjustments. Because of this same problem, strlen() will likely
 * not return the correct value for UTF8 encoded text.
 *
 * strlen() and strcmp() should still work correctly since they simply look at all
 * bits leading up to '\0'. UTF8 encoding should not be an issue.
 * 
 * ASCII encoded only truly utilize 7 out of the 8 bits available to them
 * The first bit is always a 0
 * UTF8 is one of the many encoding formats that seek to utilize the empty
 * bit at the start
 * It may be tempting to assume that since ASCII characters always start with 0,
 * that all of the functions provided in this file should work perfectly with 
 * ASCII encoded Strings and file. That should be the case, but keep extended ASCII
 * and other encoding formats in mind. UTF8 is not the only encoding format that 
 * sought to utilize the 0 bit at the start of characters. Other encoding formats
 * replace the 0 bit at the start of characters with 1 too, but they have different
 * meanings. The functions in this file should work with UTF8 encoded files along with 
 * ASCII files that do not utlize extended ASCII. For example, in ASCII, the bits for
 * a lowercase 'p' in are "0111 0000". However, a different encoding format may use 
 * the 0 at the start that ASCII doesn't use for some other purpose. The encoding format
 * could have its own meaning for "1111 0000". My UTF8 functions will interpret this as
 * meaning, "This is a UTF8 character. Therefore, the next 3 bytes are trail bytes." This
 * would be an incorrect assumption if the file is not UTF8 encoded. For example, the 
 * trueLineCharacterCountUTF8() function would skip the next three bytes. If the file
 * is not UTF8 encoded, it may return an underepresentation of the number of characters
 * in the file.
 */

/* Prints the received File
 * UTF8 encoded characters are omitted
 */
void printFileOmitUTF8(FILE *file);

/* Prints the received File
 * Instead of printing the character,
 * if the first bits of a character are:
 * "11110", then "<11110>" is printed
 * "1110", then "<1110>" is printed
 * "110", then "<110>" is printed
 */
void printFileIndicateUTF8(FILE *file);

/* Prints the received file
 * If the first bit of a character is 1,
 * then all of the bits in that char are printed
 * within "<>"
 */
void printFileRevealUTF8(FILE *file);

/* Returns the true character count for a UTF8 encoded String
 */
int trueLineCharacterCountUTF8(char *line);

/* Returns the true character count for a UTF8 encoded File
 */
int trueFileCharacterCountUTF8(FILE *file);

#endif
