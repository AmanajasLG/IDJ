#pragma once 
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/GameObject.h"
#include <vector>
#include <memory>

/*
State é a responsável pela lógica específica do seu jogo. Game conhece apenas a manipulação do estado do jogo de maneira genérica, e vai chamar as funções de State sem saber, necessariamente, como ele se comporta.
*/

class State {
private:
    Sprite *bg;
    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;

public:  

    State();

    ~State();

    bool QuitRequested();

    void LoadAssets();

    void Update(float dt);

    void Render();

    void Input();

    void AddObject(int mouseX, int mouseY);
};
