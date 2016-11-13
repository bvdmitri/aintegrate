#ifndef INTEGRATE_PARAMETERSREADER_H
#define INTEGRATE_PARAMETERSREADER_H

#include <string>
#include <cstring>
#include <cstdlib>

class ParametersReader {
public:
    double a, b;
    double eps;
    bool answer;
    bool skip;

    ParametersReader(std::string path);
    ParametersReader(const ParametersReader &other);
    virtual ~ParametersReader();
};


#endif //INTEGRATE_PARAMETERSREADER_H
