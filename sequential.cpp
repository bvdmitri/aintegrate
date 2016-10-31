#include <tbb/tbb.h>
#include "src/integrate/Integrate.h"
#include "src/utils/ParametersReader.h"
#include "functions.h"

void test(const std::function<double(double)> &f, const ParametersReader &p) {
    Integrate sequential = Integrate(Sequential, p.eps, f);

    Timer timer("Sequential");
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
    ParametersReader p2("p2.txt");

    test(f1, p1);
    test(f2, p2);
    return 0;
}