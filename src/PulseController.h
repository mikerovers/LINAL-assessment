#ifndef LINAL_ASSESSMENT_PULSECONTROLLER_H
#define LINAL_ASSESSMENT_PULSECONTROLLER_H


#include "Matrix.h"

class PulseController
{
public:
    explicit PulseController(Matrix &target, double minSize, double maxSize, double scaling);
    void act();
private:
    Matrix &target;
    double scaling;
    double minSize;
    double maxSize;
    bool shrinking;
};


#endif //LINAL_ASSESSMENT_PULSECONTROLLER_H
