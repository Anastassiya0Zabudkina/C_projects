#include <stdbool.h>

#ifndef PI_CALCULATION_H
#define PI_CALCULATION_H

struct coordinates {
    double x, y;
};

void random_coordinates(struct coordinates *coords);
bool is_inside_circle(struct coordinates *coords);
double monte_carlo_method(double n);

#endif