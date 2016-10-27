#include <tbb/tbb.h>
#include "src/integrate/Integrate.h"
#include "src/utils/ParametersReader.h"
#include "functions.h"

void test(const std::function<double(double)> &f, const ParametersReader &p) {
    Integrate sequential = Integrate(TBB, p.eps, f);

    Timer timer("TBB");
    timer.start();
    double answer = sequential.integrate(p.a, p.b);
    timer.end();
    timer.printExecutionTime();
    if (p.answer) {
        printf("Answer: %f\n", answer);
    }
}

int main(int argc, char **argv) {
    ParametersReader p1("p1.txt");

    test(f1, p1);
    return 0;
}