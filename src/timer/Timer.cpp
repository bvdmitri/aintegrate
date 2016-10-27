#include "Timer.h"

Timer::Timer() {
    _start = 0.0;
    _end = 0.0;
    _name = "";
}

Timer::Timer(std::string name) {
    _start = 0.0;
    _end = 0.0;
    _name = name;
}

void Timer::start() {
    _start = timeSinceProgramStarts();
}

void Timer::end() {
    _end = timeSinceProgramStarts();
}

void Timer::setName(std::string name) {
    this->_name = name;
}

double Timer::getExecutionTime() const{
    return _end - _start;
}

void Timer::printExecutionTime() const {
    std::cout << _name << " Execution time: " << getExecutionTime() << std::endl;
}

double Timer::timeSinceProgramStarts() const {
    timeval time;
    gettimeofday(&(time), NULL);
    return (double) time.tv_sec + (double) time.tv_usec / (1000.0 * 1000.0);
}

