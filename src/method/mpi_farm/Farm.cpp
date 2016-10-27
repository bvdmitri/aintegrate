#include "Farm.h"

Farm::Farm(int nodes_num, double a, double b, double tau) {
    this->nodes_num = nodes_num;
    this->availableNodes = (int *) calloc((size_t) nodes_num, sizeof(int));
    this->availableNodesCount = nodes_num - 1;
    this->a = a;
    this->b = b;
    this->tau = tau;
    this->answer = 0.0;


    this->jobCount = 0;
    this->jobs = (double *) calloc(FARM_JOBS_BUFFER_SIZE, sizeof(double));
    //Buf structure
    //0 - a
    //1 - b
    //2 - tau, if tau < 0, a = y or exit job

    this->message_buffer = (double *) calloc(FARM_MPI_BUFFER_SIZE, sizeof(double));
    MPI_Buffer_attach(message_buffer, FARM_MPI_BUFFER_SIZE * sizeof(double));
    //Main node is always busy
    availableNodes[0] = 1;
}

void Farm::SendInitialJobs() {
    double shift = (b - a) / (nodes_num - 1);
    double *buf = (double *) calloc(3, sizeof(double));
    for (int i = 0; i < nodes_num - 1; i++) {
        buf[0] = a + shift * i;
        buf[1] = buf[0] + shift;
        buf[2] = tau;

        MPI_Bsend(buf, 3, MPI_DOUBLE, i + 1, JOB_SEND_TAG, MPI_COMM_WORLD);
        availableNodes[i + 1] = 1;
        availableNodesCount -= 1;
    }
}

void Farm::work() {
    double buf[3];
    MPI_Status status;
    while (true) {
        MPI_Recv(buf, 3, MPI_DOUBLE, MPI_ANY_SOURCE, JOB_SAVE_OR_RESULT_TAG, MPI_COMM_WORLD, &status);
        int source = status.MPI_SOURCE;

        if (buf[2] < 0.0) {
            //Node send result
            answer += buf[0];
            if (jobCount != 0) {
                buf[0] = jobs[(jobCount - 1) * 3 + 0];
                buf[1] = jobs[(jobCount - 1) * 3 + 1];
                buf[2] = jobs[(jobCount - 1) * 3 + 2];
                jobCount -= 1;

                MPI_Bsend(buf, 3, MPI_DOUBLE, source, JOB_SEND_TAG, MPI_COMM_WORLD);
            } else {
                availableNodes[source] = 0;
                availableNodesCount += 1;
                if (availableNodesCount == (nodes_num - 1)) {
                    KillWorkers();
                    break;
                }
            }
        } else {
            //Node send job
            if (availableNodesCount != 0) {
                for (int i = 1; i < nodes_num; i++) {
                    if (availableNodes[i] == 0) {
                        MPI_Bsend(buf, 3, MPI_DOUBLE, i, JOB_SEND_TAG, MPI_COMM_WORLD);
                        availableNodes[i] = 1;
                        availableNodesCount -= 1;
                        break;
                    }
                }
            } else {
                jobs[jobCount * 3 + 0] = buf[0];
                jobs[jobCount * 3 + 1] = buf[1];
                jobs[jobCount * 3 + 2] = buf[2];
                jobCount += 1;
            }
        }

    }
}

void Farm::KillWorkers() {
    double buf[3];
    buf[2] = -1.0;
    for (int i = 1; i < nodes_num; i++) {
        MPI_Bsend(buf, 3, MPI_DOUBLE, i, JOB_SEND_TAG, MPI_COMM_WORLD);
    }
}

double Farm::Result() {
    return answer;
}

Farm::~Farm() {
    free(jobs);
    int size = FARM_MPI_BUFFER_SIZE * sizeof(double);
    MPI_Buffer_detach(message_buffer, &size);
    free(message_buffer);
}

