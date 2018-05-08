#pragma once 
#include "../include/Component.h"
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

    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    float arc;

public:

    Alien(GameObject &associated, int nMinions);

    ~Alien();

    void Start();

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    int ClosestMinion();
};
