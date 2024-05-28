#include "prime.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

/* return true if n is prime, false otherwise */
bool is_prime(long n) {
    if (n == 2) {
        return true;
    }
    if (n > 2) {
        if (n % 2 == 1) {
            int j = 0;
            for (int i = 3; i < n; i += 2) {
                if (n % i == 0) {
                    j++;
                }
            }
            if (j == 0) {
                return true;
            }
        }

    }

    return false;
}

/* return the nth prime number */
long nth_prime(int n) {
    int counter = 1;
    long result = 0;
    if (n < 1) {return 0;}
    if (n == 1) {return 2;}
    for (int i = 3; counter < n; i += 2) {
        if (is_prime(i) == true) {
            counter++;
            result = i;
        }
    }
    return result;
}

