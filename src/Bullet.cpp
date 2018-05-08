#include "../include/Bullet.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated){
    Sprite *spriteS = new Sprite(associated,sprite);
    spriteS->arc = angle;
    associated.AddComponent(spriteS);
    
    associated.box.w = spriteS->GetWidth();
    associated.box.h = spriteS->GetHeight();

    this->speed.x = speed * cos(angle);
    this->speed.y = speed * sin(angle);

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