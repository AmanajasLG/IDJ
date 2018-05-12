#include "../include/Bullet.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, bool targetsPlayer, int numFrames) : Component(associated){
    Sprite *spriteS = new Sprite(associated,sprite,numFrames);
    spriteS->arc = angle;
    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
    associated.AddComponent(spriteS);
    
    associated.box.w = spriteS->GetWidth();
    associated.box.h = spriteS->GetHeight();

    this->speed.x = speed * cos(angle);
    this->speed.y = speed * sin(angle);

    this->targetsPlayer = targetsPlayer;    

    distanceLeft = maxDistance;
    this->damage = damage;
}

void Bullet::Update(float dt){
    
    if(distanceLeft - sqrt(pow(speed.x*dt,2) + pow(speed.y*dt,2)) <= 0){
        associated.RequestDelete();
    }else{
        distanceLeft -= sqrt(pow(speed.x*dt,2) + pow(speed.y*dt,2));
        associated.box.x += speed.x*dt;
        associated.box.y += speed.y*dt; 
    }
}

void Bullet::Render(){

}

bool Bullet::Is(std::string type){
    return strcmp(type.c_str(),"Bullet") == 0;
}

int Bullet::GetDamage(){
    return damage;
}

void Bullet::NotifyCollision(GameObject &other){
    if((other.GetComponent("Alien") != nullptr && !targetsPlayer) ||
    (other.GetComponent("PenguinBody") != nullptr && targetsPlayer)){
        associated.RequestDelete();
    }    
}