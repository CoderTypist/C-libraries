#ifndef _cjbstring_h_
#define _cjbstring_h_

/* Written by Christian Bargraser October 2018 */

/* Returns a String that contains the received String and has the char
 * Appended to the end
 * This function can receive a char* that has not had memory dynamically
 * allocated for it
 */
char* AppendChar(char *original, char c);

/* char* original must have dynamically allocated memory
 * The program will crash if the String was not dynamically allocated
 * Returns -1 if original is NULL
 * You must use AppendChar if the String was not dynamically allocated
 * You should use AppendChar() if there exists the possibility that the 
 * received String was not dynamically allocated*/
 
int AppendCharToMallocd(char* original, char c);

/* Returns a String that starts at startIndex
 * The returned String ends at and includes endIndex
 */
char* Substring(char *original, int startIndex, int endIndex);

/* A String containing the char is returned */
char* CharToString(char c);

/* Receives a pointer and frees the memory that it is pointing to
 * However, if the pointer is pointing to a structure, and the structure
 * Has attributes that are pointers, the memory that those pointers point
 * to will not be freed
 * Call this method as follows:
 * nfree((void*)&variable);
 */
void nfree(void **dp);

/* Thre received String is freed and set equal to NULL */
void StringFree(char **dp);

#endif
