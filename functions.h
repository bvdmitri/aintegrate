#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <functional>
#include <cmath>

const std::function<double(double)> &f1 = [](double x) {
    return sin(x) * cos(x) + sin(x) * cos(x) * log(sqrt(x + 1));
};


#endif