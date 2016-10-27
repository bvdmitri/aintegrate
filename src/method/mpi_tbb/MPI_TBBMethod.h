#ifndef MPI_TBBMETHOD_H
#define MPI_TBBMETHOD_H

#include <mpi.h>
#include <cmath>
#include <functional>
#include <tbb/tbb.h>
#include "../IntegrationMethod.h"

class MPI_TBBMethod : public IntegrationMethod {
	double tbb_run(double a, double b);
public:
    MPI_TBBMethod(double eps, const std::function<double(double)> &f);

    virtual double integrate(double a, double b);

    virtual ~MPI_TBBMethod();
};

#endif // !MPI_TBBMETHOD_H