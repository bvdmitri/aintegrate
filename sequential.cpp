#include <tbb/tbb.h>
#include "src/integrate/Integrate.h"
#include "src/utils/ParametersReader.h"
#include "functions.h"

void test(const std::function<double(double)> &f, const ParametersReader &p) {
    if (p.skip) {
        printf("Function skipped\n");
        return;
    }
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
    ParametersReader p3("p3.txt");
    ParametersReader p4("p4.txt");

    test(f1, p1);
    test(f2, p2);
    test(f3, p3);
    test(f4, p4);
    return 0;
}