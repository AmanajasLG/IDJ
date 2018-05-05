#pragma once 
#include "../include/Component.h"
#include <iostream>
#include <string>
using namespace std;

/*
Face é um “inimigo” com uma determinada quantidade de HP.
*/
class Face : public Component{
private:
    int hitpoints;

public:
    Face(GameObject &associeted);

    void Damage(int damage);

    void Update(float dt);

    void Render();

    bool Is(std::string type);

    void Start();
};