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
    //Sprite *bg;
    //Music music;

public:  

    State();

    virtual ~State();

    void virtual LoadAssets() = 0;

    void virtual Update(float dt) = 0;

    void virtual Render() = 0;

    void virtual Start() = 0;

    void virtual Pause() = 0;

    void virtual Resume() = 0;

    std::weak_ptr<GameObject> virtual AddObject(GameObject *go);

    std::weak_ptr<GameObject> virtual GetObjectPtr(GameObject *go);

    bool QuitRequested();

    bool PopRequested();

protected:
    bool popRequested;
    bool quitRequested;
    bool started;

    std::vector< std::shared_ptr< GameObject > > objectArray;

    void StartArray();

    void virtual UpdateArray(float dt);

    void virtual RenderArray();
};
