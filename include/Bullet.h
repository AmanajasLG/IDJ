#pragma once 
#include "../include/Component.h"

class Bullet : public Component{
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
public:
    bool targetsPlayer;

    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool targetsPlayer, int numFrames = 1);

    void Update(float dt);

    void Render();

    bool Is(std::string type); 

    int GetDamage();

    void NotifyCollision(GameObject &other);
};