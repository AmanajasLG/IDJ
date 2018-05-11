#pragma once
#include "SDL_include.h"
#include <iostream>
#include <string>
using namespace std;

class Timer{
private:
    float time;
    float secondsToSelfDestruct;
    Timer *selfDestructCount;

public:
    

    Timer(float secondsToSelfDestruct = 0);

    bool Update(float dt);

    void Restart();

    float Get();
};