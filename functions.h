#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <functional>
#include <cmath>

const std::function<double(double)> &f1 = [](double x) {
    return sin(x) * cos(x) + sin(x) * cos(x) * log(sqrt(x + 1));
};

const std::function<double(double)> &f2 = [](double x) {
	return (sin(sin(sin(sin(sin(sin(x + sqrt(x) + sqrt(sqrt(x)))))))) * cos(cos(cos(cos(cos(log(x + 1)))))));
};

const std::function<double(double)> &f3 = [](double x) -> double {
	if (x <= 10 * M_PI) {

		return (sin(500 * x));
	} else {
		return (double) 0.0;
	}
};

const std::function<double(double)> &f4 = [](double x) -> double {
    return sin(500 * x);
};

#endif