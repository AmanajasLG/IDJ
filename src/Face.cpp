#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Sprite.h"
#include "../include/GameObject.h"

Face::Face(GameObject &associeted) : Component (associeted){
    hitpoints = 30;
}

/*
Deve reduzir os hitpoints na quantidade passada.
*/
void Face::Damage(int damage){
    damage -= hitpoints;
    if(damage<=0){
        associeted.RequestDelete();
        Sprite* sprite = (Sprite*)associeted.GetComponent("Sprite");
        associeted.RemoveComponent(sprite);
        Sound* sound = (Sound*)associeted.GetComponent("Sound");
        if(sound != nullptr){
            sound->Play();
        }
    }
}

void Face::Update(float dt){

}

void Face::Render(){

}

bool Face::Is(std::string type){
    if(strcmp(type.c_str(),"Face") == 0){
        return true;
    }
    return false;
}