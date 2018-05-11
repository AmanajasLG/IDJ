#pragma once 
#include "../include/Component.h"
#include "../include/Vec2.h"

class PenguinBody : public Component{
private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

public:
    static PenguinBody *player;

    PenguinBody(GameObject &associated);

    ~PenguinBody();

    void Start();

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    void NotifyCollision(GameObject &other);

    Vec2 GetPos();
};