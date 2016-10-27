#ifndef INTEGRATE_TBBMETHOD_H
#define INTEGRATE_TBBMETHOD_H

#include <cmath>
#include <tbb/tbb.h>
#include "../IntegrationMethod.h"

class TBBMethod : public IntegrationMethod {
public:
    TBBMethod(double eps, const std::function<double(double)> &f);

    virtual double integrate(double a, double b);

    virtual ~TBBMethod();
};


#endif //INTEGRATE_TBBMETHOD_H
