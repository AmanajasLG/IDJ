#include "../include/Bullet.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated){
    Sprite *spriteS = new Sprite(associated,sprite);
    associated.AddComponent(spriteS);
    
    associated.box.w = spriteS->GetWidth();
    associated.box.h = spriteS->GetHeight();
    //Vec2 boxRot;
    //boxRot.x = associated.box.w;
    //boxRot.y = associated.box.h;

    //boxRot.GetRotated(angle);

    //associated.box.x += boxRot.x + associated.box.w/2;
    //associated.box.y += boxRot.y + associated.box.h/2;

    this->speed.x = speed * cos(angle);
    this->speed.y = speed * sin(angle);

    distanceLeft = maxDistance;
    this->damage = damage;
}

void Bullet::Update(float dt){
    distanceLeft -= sqrt(pow(speed.x*dt,2) + pow(speed.y*dt,2));
    if(distanceLeft <= 0){
        float angle = acos(this->speed.x/20);
        this->speed.x = distanceLeft * cos(angle);
        this->speed.y = distanceLeft * sin(angle);
        associated.box.x += speed.x;
        associated.box.y += speed.y;
        associated.RequestDelete();
    }else{
        associated.box.x += speed.x*dt;
        associated.box.y += speed.y*dt; 

        std::cout<<"BULLET BOX X = "<<associated.box.x<<endl;
        std::cout<<"BULLET BOX Y = "<<associated.box.y<<endl;
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