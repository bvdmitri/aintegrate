#include <tbb/tbb.h>
#include <mpi.h>
#include "src/integrate/Integrate.h"
#include "src/utils/ParametersReader.h"
#include "functions.h"

void test(const std::function<double(double)> &f, const ParametersReader& p) {
    Integrate mpi_tbb = Integrate(Method::MPI_TBB, 0.001, f);

    Timer timer("MPI_TBB");
    timer.start();
    double answer = mpi_tbb.integrate(p.a, p.b);
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
    ParametersReader p1("p1.txt");
    ParametersReader p2("p2.txt");

    test(f1, p1);
    test(f2, p2);

    MPI_Finalize();
    return 0;
}