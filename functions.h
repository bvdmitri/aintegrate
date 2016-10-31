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

const std::function<double(double)> &f3 = [](double x) {
	if (x <= 10000) {
		return (sin(sin(sin(sin(sin(sin(x + sqrt(x) + sqrt(sqrt(x)))))))) * cos(cos(cos(cos(cos(log(x + 1)))))));	
	} else {
		return 0.249609;
	}
};

#endif