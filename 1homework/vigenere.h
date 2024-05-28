#ifndef VIGENERE_H
#define VIGENERE_H

/* Definition of useful constants */
/* Maximal length of the codeword */
#define MAXCODE 10

/* Maximal length of the text/cipher */
#define MAXTEXT 100

/* Operation CODE = encrypt, DECODE = decrypt */
#define CODE    0
#define DECODE  1

void coding(char *codeword, char *plaintext, char *result, int operation);

#endif