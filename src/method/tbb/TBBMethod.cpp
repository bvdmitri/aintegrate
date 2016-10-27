//
// Created by Dmitri Bagaev on 25.10.16.
//

#include "TBBMethod.h"

TBBMethod::TBBMethod(double eps, const std::function<double(double)> &f) : IntegrationMethod(eps, f) {}

double TBBMethod::integrate(double a, double b) {
    double x = simpson(a, b, 4);
    double y = simpson(a, b, 8);
    if (fabs(x - y) < eps) {
        return y;
    } else {
        tbb::task_group group;

        group.run([&] {
            x = integrate(a, (a + b) / 2.0);
        });

        group.run_and_wait([&] {
            y = integrate((a + b) / 2.0, b);
        });

        return x + y;
    }
}

TBBMethod::~TBBMethod() {}
