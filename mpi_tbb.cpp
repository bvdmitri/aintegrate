#include <tbb/tbb.h>
#include <mpi.h>
#include "src/integrate/Integrate.h"
#include "src/utils/ParametersReader.h"
#include "functions.h"

void test(const std::function<double(double)> &f, const ParametersReader& p) {
    int id;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    if (p.skip && id == 0) {
        printf("Function skipped\n");
        return;
    }
    Integrate mpi_tbb = Integrate(Method::MPI_TBB, p.eps, f);

    Timer timer("MPI_TBB");
    timer.start();
    double answer = mpi_tbb.integrate(p.a, p.b);
    timer.end();

    if (id == 0) {
        timer.printExecutionTime();
        if (p.answer) {
            printf("Answer: %f\n", answer);
        }
    }


}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD,  &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    ParametersReader p1("p1.txt");
    ParametersReader p2("p2.txt");
    ParametersReader p3("p3.txt");
    ParametersReader p4("p4.txt");

    if (rank == 0) {
        printf("MPI_TBB: %d nodes\n", size);
    }
    test(f1, p1);
    test(f2, p2);
    test(f3, p3);
    test(f4, p4);

    if (rank == 0) {
        printf("============================\n");
    }

    MPI_Finalize();
    return 0;
}