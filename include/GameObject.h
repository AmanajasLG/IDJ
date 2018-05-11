#pragma once 
#define INCLUDE_SDL
#include "../include/SDL_include.h"
#include "../include/Rect.h"
#include "../include/Component.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Component;
/*
GameObject é um agrupador de lógicas que estarão implementadas em seus componentes. 
Todo GameObject (GO para ficar mais curto) possui uma posição no jogo (box).
*/
class GameObject{
private:
    std::vector<unique_ptr<Component>> components;
    bool isDead;
    bool started;

public:
    Rect box;
    double angleDeg;
    
    GameObject();

    ~GameObject();

    void Update(float dt);

    void Render();

    bool IsDead();

    void RequestDelete();

    void AddComponent(Component *cpt);

    void RemoveComponent(Component *cpt);

    Component* GetComponent(std::string type);    

    void Start();

    void NotifyCollision(GameObject &other);
};