#ifndef STEPCONTROLLER_H_INCLUDED
#define STEPCONTROLLER_H_INCLUDED
#include "TextManager.h"
class StepController {
protected:
    SDL_Renderer *renderer = NULL;
    SDL_Rect stepsR, levelNumberR;
    TextManager textManager;
    static TextInfo steps, levelNumber;
    static int step;
public:
    StepController();
    StepController(SDL_Renderer *renderer_);
    StepController(int value, SDL_Renderer *renderer_);
    int getStep();
    void setStep(int value, SDL_Renderer *renderer_);
    void setStep(int value, SDL_Renderer *renderer_, int level);
    void addStep();
    void passStep();
    void render();
    void destroy();
    static int level;
};

#endif // STEPCONTROLLER_H_INCLUDED
