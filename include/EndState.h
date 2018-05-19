#pragma once 
#include "../include/State.h"

class EndState : public State{
private:
    Music backgroundMusic;

public:
    EndState(bool playerVictory);

    ~EndState();

    void LoadAssets();

    void Update(float dt);

    void Render();

    void Start();

    void Pause();

    void Resume();
};