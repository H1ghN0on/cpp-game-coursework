#include "StepController.h"

int StepController :: step;

StepController :: StepController() {
}

StepController :: StepController(int value) {
    step = value;
}

void StepController :: setStep(int value) {
    step = value;
}

void StepController :: passStep() {
    step--;
}

void StepController :: addStep() {
    step++;
}

int StepController :: getStep() {
    return step;
}

