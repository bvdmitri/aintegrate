#ifndef INTEGRATE_MPIFARMMETHOD_H
#define INTEGRATE_MPIFARMMETHOD_H

#include <mpi.h>
#include <cmath>
#include <functional>
#include "../IntegrationMethod.h"

class MPIFarmMethod: public IntegrationMethod {
public:
    MPIFarmMethod(double eps, const std::function<double(double)> &f);

    virtual double integrate(double a, double b);

    virtual ~MPIFarmMethod();
};


#endif //INTEGRATE_MPIFARMMETHOD_H
