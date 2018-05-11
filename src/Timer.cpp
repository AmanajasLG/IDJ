#include "../include/Timer.h"

Timer::Timer(float secondsToSelfDestruct){
    time = 0;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
}

bool Timer::Update(float dt){
    time += dt;
    
    if(secondsToSelfDestruct > 0){
        if(time > secondsToSelfDestruct){
            return true;
        }
    }

    return false;    
}

void Timer::Restart(){
    time = 0;
}

float Timer::Get(){
    return time;
}