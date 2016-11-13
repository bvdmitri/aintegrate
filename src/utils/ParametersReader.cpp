#include "ParametersReader.h"

ParametersReader::ParametersReader(std::string path) {
    this->answer = false;
    this->skip = false;
    FILE *parameters_file = fopen(path.c_str(), "r");
    if (!parameters_file) {
        fprintf(stderr, "No parameters file found\n");
        exit(1);
    }
    char *tmp = (char *) calloc(256, sizeof(char));
    char *parameterName = (char *) calloc(128, sizeof(char));
    char *parameterValue = (char *) calloc(128, sizeof(char));
    while (!feof(parameters_file) && fgets(tmp, 256, parameters_file)) {
        char *line = tmp;
        //Comment str
        if (line[0] == '#') continue;
        sscanf(line, "%s %s", parameterName, parameterValue);

        if (strcmp(parameterName, "a") == 0) {
            this->a = atof(parameterValue);
        }

        if (strcmp(parameterName, "b") == 0) {
            this->b = atof(parameterValue);
        }

        if (strcmp(parameterName, "eps") == 0) {
            this->eps = atof(parameterValue);
        }

        if (strcmp(parameterName, "answer") == 0) {
            if (strcmp(parameterValue, "true") == 0) {
                this->answer = true;
            }
        }

        if (strcmp(parameterName, "skip") == 0) {
            if (strcmp(parameterValue, "true") == 0) {
                this->skip = true;
            }
        }

    }
    free(parameterValue);
    free(parameterName);
    free(tmp);
    fclose(parameters_file);
}

ParametersReader::ParametersReader(const ParametersReader &other) : a(other.a), b(other.b), eps(other.eps), answer(other.answer) {}

ParametersReader::~ParametersReader() {}


