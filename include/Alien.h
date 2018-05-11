#pragma once 
#include "../include/Component.h"
#include "../include/Timer.h"
#include <queue>

class Alien : public Component{
private:
    class Action{
    public:
        enum ActionType{MOVE, SHOOT};
        Vec2 pos;
        ActionType type;

        Action(ActionType type, float x, float y);
    };

    enum AlienState{MOVING, RESTING};
    AlienState state; 
    Timer restTimer;
    Vec2 destination;
    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    

public:
    int alienCount;

    Alien(GameObject &associated, int nMinions);

    ~Alien();

    void Start();

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    //int ClosestMinion(Vec2 target);
    int ClosestMinion();

    void NotifyCollision(GameObject &other);
};
