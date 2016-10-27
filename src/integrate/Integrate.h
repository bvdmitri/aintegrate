#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <functional>
#include <string>
#include "../timer/Timer.h"
#include "../method/IntegrationMethod.h"
#include "../method/sequential/SequentialMethod.h"
#include "../method/tbb/TBBMethod.h"
#include "../method/mpi_tbb/MPI_TBBMethod.h"
#include "../method/mpi_farm/MPIFarmMethod.h"

enum Method {
    Sequential,
    TBB,
    MPI_TBB,
    MPI_FARM
};

class Integrate {
private:
    Method method_name;
    IntegrationMethod *method;
public:
    Integrate(Method method, double eps, const std::function<double(double)> &f);

    double integrate(double a, double b) const;

    ~Integrate();
};

#endif // !INTEGRATE_H