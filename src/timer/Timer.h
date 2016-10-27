#ifndef INTEGRATE_TIMER_H
#define INTEGRATE_TIMER_H


#include <sys/time.h>
#include <iostream>

class Timer {
private:
    double _start;
    double _end;
    std::string _name;
public:
    Timer();
    Timer(std::string name);

    void start();
    void end();

    void setName(std::string name);

    double getExecutionTime() const;
    void printExecutionTime() const;

    double timeSinceProgramStarts() const;
};


#endif //INTEGRATE_TIMER_H
