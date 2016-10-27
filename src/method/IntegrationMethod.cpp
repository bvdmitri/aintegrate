#include "IntegrationMethod.h"

double IntegrationMethod::simpson(double a, double b, int k) {
    double h = (b - a) / ((double) 2 * k);
    double answer = 0.0;
    for (int j = 1; j < 2 * k; j += 2) {
        answer += (f(a + h * (j - 1)) + 4 * f(a + h * j) +
                   f(a + h * (j + 1)));
    }
    return h * answer / 3;
}

