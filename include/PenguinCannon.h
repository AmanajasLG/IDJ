#pragma once 
#include "../include/Component.h"
#include "../include/Timer.h"

class PenguinCannon : public Component{
private:
    std::weak_ptr<GameObject> pbody;
    float angle;
    Timer timer;

public:
    PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    void Shoot();

    void NotifyCollision(GameObject &other);
};