#ifndef SEQUENTIAL_METHOD_H
#define SEQUENTIAL_METHOD_H

#include <cmath>
#include "../IntegrationMethod.h"

class SequentialMethod : public IntegrationMethod {
public:
    SequentialMethod(double eps, const std::function<double(double)> &f);

    virtual double integrate(double a, double b);

    virtual ~SequentialMethod();
};

#endif // !SEQUENTIAL_METHOD_H