#ifndef INTEGRATION_METHOD_H
#define INTEGRATION_METHOD_H

#include <functional>

class IntegrationMethod {
protected:
    const double eps;
    const std::function<double(double)> &f;

    double simpson(double a, double b, int k);
public:
    IntegrationMethod(double eps, const std::function<double(double)> &f) : eps(eps), f(f) {};

    virtual double integrate(double a, double b) = 0;

    virtual ~IntegrationMethod() {};
};

#endif // !INTEGRATION_METHOD_H