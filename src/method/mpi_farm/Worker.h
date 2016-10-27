#ifndef INTEGRATE_WORKER_H
#define INTEGRATE_WORKER_H

#include <functional>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <mpi.h>
#include "Farm.h"

#define WORKER_MPI_BUFFER_SIZE 65536

class Worker {
private:
    double *buf;
    double *message_buffer;

    const std::function<double(double)> &f;

    double simpson(double a, double b, int k);

public:
    Worker(const std::function<double(double)> &f);

    void work();

    void GetJob();

    void Calculate();

    void SaveJob(double a, double b, double tau);

    void SendResult(double result);

    ~Worker();
};


#endif //INTEGRATE_WORKER_H
