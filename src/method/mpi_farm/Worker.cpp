#include <cmath>
#include "Worker.h"

Worker::Worker(const std::function<double(double)> &f): f(f) {
    this->buf = (double *) calloc(16, sizeof(double));
    this->message_buffer = (double *) calloc(WORKER_MPI_BUFFER_SIZE, sizeof(double));
    MPI_Buffer_attach(message_buffer, WORKER_MPI_BUFFER_SIZE * sizeof(double));
}

void Worker::work() {
    while (true) {
        GetJob();
        if (buf[2] > 0.0) {
            Calculate();
        } else {
            break;
        }
    }
}

void Worker::GetJob() {
    MPI_Recv(buf, 3, MPI_DOUBLE, 0, JOB_GET_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void Worker::Calculate() {
    double a = buf[0];
    double b = buf[1];
    double tau = buf[2];

    while (true) {
        double x = simpson(a, b, 4);
        double y = simpson(a, b, 8);

        if (fabs(x - y) < tau) {
            SendResult(y);
            break;
        } else {
            SaveJob(a, (a + b) / 2, tau / 2);
            a = (a + b) / 2;
            tau = tau / 2;
        }

    }
}

void Worker::SaveJob(double a, double b, double tau) {
    double job[3];
    job[0] = a;
    job[1] = b;
    job[2] = tau;
    MPI_Bsend(job, 3, MPI_DOUBLE, 0, JOB_SAVE_OR_RESULT_TAG, MPI_COMM_WORLD);
}

void Worker::SendResult(double result) {
    double r[3];
    r[0] = result;
    r[1] = 0.0;
    r[2] = -1.0;
    MPI_Bsend(r, 3, MPI_DOUBLE, 0, JOB_SAVE_OR_RESULT_TAG, MPI_COMM_WORLD);
}

Worker::~Worker() {
    free(buf);
    int size = WORKER_MPI_BUFFER_SIZE * sizeof(double);
    MPI_Buffer_detach(message_buffer, &size);
    free(message_buffer);
}


double Worker::simpson(double a, double b, int k) {
    double h = (b - a) / ((double) 2 * k);
    double answer = 0.0;
    for (int j = 1; j < 2 * k; j += 2) {
        answer += (f(a + h * (j - 1)) + 4 * f(a + h * j) +
                   f(a + h * (j + 1)));
    }
    return h * answer / 3;
}