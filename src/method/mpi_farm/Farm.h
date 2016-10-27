#ifndef INTEGRATE_FARM_H
#define INTEGRATE_FARM_H


#include <cstdlib>
#include <cstdio>
#include <mpi.h>

#define JOB_GET_TAG 0
#define JOB_SEND_TAG 0

#define JOB_SAVE_OR_RESULT_TAG 1

#define FARM_JOBS_BUFFER_SIZE 65536
#define FARM_MPI_BUFFER_SIZE 65536

class Farm {
private:
    int nodes_num;
    int *availableNodes;
    int availableNodesCount;
    int jobCount;
    double *jobs;

    double a;
    double b;
    double tau;

    double answer;
    double *message_buffer;
public:
    Farm(int nodes_num, double a, double b, double tau);

    void SendInitialJobs();
    void work();
    void KillWorkers();

    double Result();
    ~Farm();
};


#endif //INTEGRATE_FARM_H
