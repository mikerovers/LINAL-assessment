#include "PulseController.h"

PulseController::PulseController(Matrix &target, double minSize, double maxSize, double scaling)
        : target(target), scaling(scaling), minSize(minSize), maxSize(maxSize), shrinking(true)
{}

void PulseController::act()
{
    if (shrinking) {
        auto scalingAmount = 1 - scaling;
        target.scale(scalingAmount, scalingAmount, scalingAmount);
    } else {
        auto scalingAmount = 1 + scaling;
        target.scale(scalingAmount, scalingAmount, scalingAmount);
    }

    if (target.getRadius() >= maxSize) {
        shrinking = true;
    } else if (target.getRadius() <= minSize) {
        shrinking = false;
    }
}

