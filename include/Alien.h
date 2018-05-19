#pragma once 
#include "../include/Component.h"
#include "../include/Timer.h"
#include <queue>

class Alien : public Component{
private:
    enum AlienState{MOVING, RESTING};
    AlienState state; 
    Timer restTimer;
    Vec2 destination;
    Vec2 speed;
    int hp;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    

public:
    int alienCount;

    Alien(GameObject &associated, int nMinions, float timeOffset);

    ~Alien();

    void Start();

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    int ClosestMinion(Vec2 target);

    void NotifyCollision(GameObject &other);

    int GetHP();
};
