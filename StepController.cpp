#include "StepController.h"

int StepController :: level;
int StepController :: step;
TextInfo StepController :: steps;
TextInfo StepController :: levelNumber;
StepController :: StepController() {

}

StepController :: StepController(SDL_Renderer *renderer_) {
    renderer = renderer_;
    stepsR.x = 15;
    stepsR.y = 780;
    levelNumberR.x = 500;
    levelNumberR.y = 780;
}

StepController :: StepController(int value, SDL_Renderer *renderer_) {
    step = value;
    string name = "Steps " + to_string(step);
    steps = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 44, renderer);
    stepsR.w = steps.width;
    stepsR.h = steps.height;
}

void StepController :: setStep(int value, SDL_Renderer *renderer_) {
    renderer = renderer_;
    step = value;
    string name = "Steps " + to_string(step);
    SDL_DestroyTexture(steps.texture);
    steps = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 44, renderer);
}

void StepController :: setStep(int value, SDL_Renderer *renderer_, int level_) {
    level = level_;
    renderer = renderer_;
    step = value;
    string name = "Steps " + to_string(step);
    string mame = "Level " + to_string(level);
    SDL_DestroyTexture(steps.texture);
    steps = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 44, renderer);
    levelNumber = textManager.renderText(mame, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 44, renderer);
    stepsR.w = steps.width;
    stepsR.h = steps.height;
    levelNumberR.w = levelNumber.width;
    levelNumberR.h = levelNumber.height;
}

void StepController :: passStep() {
    step--;
    string name = "Steps " + to_string(step);
    SDL_DestroyTexture(steps.texture);
    steps = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 44, renderer);
    stepsR.w = steps.width;
    stepsR.h = steps.height;
}
void StepController :: addStep() {
    step++;
    string name = "Steps " + to_string(step);
    SDL_DestroyTexture(steps.texture);
    steps = textManager.renderText(name, "fonts/Leo Normal.ttf", {255, 255, 255, 255}, 44, renderer);
}

void StepController :: render() {
    SDL_RenderCopy(renderer, steps.texture, NULL, &stepsR);
    SDL_RenderCopy(renderer, levelNumber.texture, NULL, &levelNumberR);
}

int StepController :: getStep() {
    return step;
}

void StepController :: destroy() {
    SDL_DestroyTexture(steps.texture);
    SDL_DestroyTexture(levelNumber.texture);
}

