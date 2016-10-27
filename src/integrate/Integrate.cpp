#include "Integrate.h"


Integrate::Integrate(Method method, double eps, const std::function<double(double)> &f) {
    this->method_name = method;
    switch (method) {
        case Sequential:
            this->method = new SequentialMethod(eps, f);
            break;
        case TBB:
            this->method = new TBBMethod(eps, f);
            break;
        case MPI_TBB:
            this->method = new MPI_TBBMethod(eps, f);
            break;
        case MPI_FARM:
            this->method = new MPIFarmMethod(eps, f);
            break;
        default:
            throw "Unsupported integration method: " + std::to_string(method);
    }
}

double Integrate::integrate(double a, double b) const {
    return method->integrate(a, b);
}

Integrate::~Integrate() { delete method; }