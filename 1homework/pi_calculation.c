#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "pi_calculation.h"

/* fill the structure with random values between -1 and 1 */
/* the definition of the structure is located in the pi_calculation.h */
void random_coordinates(struct coordinates *coords) {
    coords->x = (double)rand() / RAND_MAX * 2 - 1;
    coords->y = (double)rand() / RAND_MAX * 2 - 1;
}

/* return true if the point given in argument is inside the circle 
of center (0,0) and radius 1” */
bool is_inside_circle(struct coordinates *coords) {
    return (coords->x * coords->x + coords->y * coords->y) <= 1.0;
}

/* 
returns the pi calculation approximation after n iterations,
the monte carlo method for pi calculation works as follow:
    - draw n random points with their coordinates between -1 and  1 (you should use your random_coordinates function)
    - calculte the ratio of points inside the circle over the total number of points
    - multiply the ratio by 4 and return this value
*/
double monte_carlo_method(double n) {
    int inside_circle = 0;
    struct coordinates coords;

    for (int i = 0; i < n; i++) {
        random_coordinates(&coords);
        if (is_inside_circle(&coords)) {
            inside_circle++;
        }
    }

    return 4.0 * inside_circle / n;
} 