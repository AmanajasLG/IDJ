#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Sprite.h"
#include "../include/GameObject.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include <math.h>

Face::Face(GameObject &associeted) : Component (associeted){
    hitpoints = 30;
}

/*
Deve reduzir os hitpoints na quantidade passada.
*/
void Face::Damage(int damage){
    hitpoints -= damage;
    if(hitpoints<=0 && !associated.IsDead()){
        associated.RequestDelete();
        Sprite* sprite = (Sprite*)associated.GetComponent("Sprite");
        associated.RemoveComponent(sprite);
        Sound* sound = (Sound*)associated.GetComponent("Sound");
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
    return strcmp(type.c_str(),"Face") == 0;
}

void Face::Start(){
    
}