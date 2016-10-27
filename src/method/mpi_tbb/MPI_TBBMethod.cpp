#include "MPI_TBBMethod.h"

MPI_TBBMethod::MPI_TBBMethod(double eps, const std::function<double(double)> &f) : IntegrationMethod(eps, f) {}

double MPI_TBBMethod::tbb_run(double a, double b) {
	double x = simpson(a, b, 4);
    double y = simpson(a, b, 8);
    if (fabs(x - y) < eps) {
        return y;
    } else {
        tbb::task_group group;

        group.run([&] {
            x = tbb_run(a, (a + b) / 2.0);
        });

        group.run_and_wait([&] {
            y = tbb_run((a + b) / 2.0, b);
        });

        return x + y;
    }
}

double MPI_TBBMethod::integrate(double a, double b) {
	double answer = 0.0;
	int nodes = 1;
    MPI_Comm_size(MPI_COMM_WORLD, &nodes);

    int node_id = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &node_id);

	double h = (b - a) / (double) nodes;

	a = a + h * node_id;
    b = a + h;

    double node_answer = tbb_run(a, b);
    MPI_Barrier(MPI_COMM_WORLD);
    if (node_id == 0) {
    	answer += node_answer;
        for (int i = 1; i < nodes; i++) {
            MPI_Recv(&node_answer, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            answer += node_answer;
        }
    } else {
        MPI_Send(&node_answer, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

	return answer;
}

MPI_TBBMethod::~MPI_TBBMethod() {}