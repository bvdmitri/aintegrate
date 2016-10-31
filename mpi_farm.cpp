#include <tbb/tbb.h>
#include <mpi.h>
#include "src/integrate/Integrate.h"
#include "src/utils/ParametersReader.h"
#include "functions.h"

void test(const std::function<double(double)> &f, const ParametersReader &p) {
    Integrate mpi_farm = Integrate(Method::MPI_FARM, 0.001, f);

    Timer timer("MPI_FARM");
    timer.start();
    double answer = mpi_farm.integrate(p.a, p.b);
    timer.end();

    int id;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

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

    if (rank == 0) {
        printf("MPI_FARM: %d nodes\n", size);
    }
    test(f1, p1);
    test(f2, p2);
    test(f3, p2);
    if (rank == 0) {
        printf("============================\n");
    }
    

    MPI_Finalize();
    return 0;
}