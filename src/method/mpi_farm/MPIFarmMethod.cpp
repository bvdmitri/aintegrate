//
// Created by Dmitri Bagaev on 27.10.16.
//

#include "MPIFarmMethod.h"
#include "Farm.h"
#include "Worker.h"

MPIFarmMethod::MPIFarmMethod(double eps, const std::function<double(double)> &f) : IntegrationMethod(eps, f) {}



double MPIFarmMethod::integrate(double a, double b) {
    int nodes_num = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &nodes_num);
    if (nodes_num <= 1) {
        fprintf(stderr, "It should be at least 2 process\n");
        return 0.0;
    }

    int node_id = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &node_id);

    if (node_id == 0) {
        Farm farm = Farm(nodes_num, a, b, eps / (nodes_num - 1));
        farm.SendInitialJobs();
        farm.work();
        return farm.Result();
    } else {
        Worker worker = Worker(f);
        worker.work();
        return 0.0;
    }

}

MPIFarmMethod::~MPIFarmMethod() {}
