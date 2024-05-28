#include "vigenere.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* This function encrypts/decrypts the "plaintext" with the codeword "codeword"
based on the value of the paraneter "operation" and saves in the result variable "result".
Implement the function that was discussed during the first tutorial
*/
void coding(char *codeword, char *plaintext, char *result, int operation){
    int codewordLen = strlen(codeword);
    int textLen = strlen(plaintext);
    int codewordIndex = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char codeBase = isupper(codeword[codewordIndex % codewordLen]) ? 'A' : 'a';
            int shift = toupper(codeword[codewordIndex % codewordLen]) - 'A';
            if (codeBase == 'A') {
                shift += 26;
            }
            if (operation == 1) {
                result[i] = (plaintext[i] - base + shift + 26) % 26 + base;
            } else {
                result[i] = (plaintext[i] - base - shift + 26) % 26 + base;
            }
            codewordIndex++;
        } else {
            result[i] = plaintext[i];
        }
    }
    result[textLen] = '\0';
}
