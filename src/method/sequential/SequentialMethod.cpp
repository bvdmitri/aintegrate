#include "SequentialMethod.h"

SequentialMethod::SequentialMethod(double eps, const std::function<double(double)> &f) : IntegrationMethod(eps, f) {}

double SequentialMethod::integrate(double a, double b) {
    double x = simpson(a, b, 4);
    double y = simpson(a, b, 8);
    if (fabs(x - y) < eps) {
        return y;
    } else {
        return integrate(a, (a + b) / 2.0) + integrate((a + b) / 2.0, b);
    }
}

SequentialMethod::~SequentialMethod() {}