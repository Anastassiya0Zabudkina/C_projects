#include "palindrome.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
write a function that check whether
the given string is a palindrome or not

additionnal functions can be written to help you with this task
*/


bool palindrome(char *string) {
    int length = strlen(string);
    int middle = length/2;
    for (int i = 0; i < middle; i++){
        if(string[i] != string[length-1-i]){
            return false;
        }
    }

    return true;
}

void test_palindrome(char *string, bool expected) {
    bool result = palindrome(string);
    printf("Test: \"%s\" - Expected: %s, Got: %s\n", string, expected ? "True" : "False", result ? "True" : "False");
}
