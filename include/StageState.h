#pragma once 
#include "../include/State.h"
#include "../include/TileSet.h"

/*
State é a responsável pela lógica específica do seu jogo. Game conhece apenas a manipulação do estado do jogo de maneira genérica, e vai chamar as funções de State sem saber, necessariamente, como ele se comporta.
*/

class StageState : public State{
private:
    TileSet *tileSet;
    Music backgroundMusic;

public:  

    StageState();

    ~StageState();

    void LoadAssets();

    void Update(float dt);

    void Render();

    void Start();

    void Pause();

    void Resume();
};
