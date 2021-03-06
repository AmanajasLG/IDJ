#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include "../include/Collider.h"
#include "../include/Alien.h"
#include <math.h>

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter){
    arc = arcOffsetDeg;

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
    Sprite *sprite = new Sprite(associated, "assets/img/minion.png");
    
    float scale = (float) rand() / (RAND_MAX) + 1;
    if(scale > 1.5)
        scale -= 0.5;
    
    
    sprite->SetScale(scale,scale);
    sprite->arc = arcOffsetDeg;
    associated.AddComponent(sprite);

    std::shared_ptr<GameObject> sharedGO(this->alienCenter.lock());

    associated.box.h = sprite->GetHeight();
    associated.box.w = sprite->GetWidth();
    associated.box.x = sharedGO->box.x - associated.box.w/2;
    associated.box.y = sharedGO->box.y - associated.box.h/2;
}

Minion::~Minion(){
    

}

void Minion::Update(float dt){
    
    if(alienCenter.lock() == nullptr){
        return;
    }    

    std::shared_ptr<GameObject> sharedGO(alienCenter.lock());
    
    Sprite *sprite = (Sprite*) associated.GetComponent("Sprite");

    Vec2 minionPos = Vec2(130, 0);

    
    arc -= dt*M_PI;
    minionPos.GetRotated(arc);
    
    sprite->arc = arc;
    
    Vec2 objPos = objPos.AddVectors(minionPos, Vec2( sharedGO->box.x - associated.box.w/2 + sharedGO->box.w/2, sharedGO->box.y - associated.box.h/2 + sharedGO->box.h/2));
    associated.box.x = objPos.x;
    associated.box.y = objPos.y;
    
}

void Minion::Render(){

}

bool Minion::Is(std::string type){
    return strcmp(type.c_str(),"Minion") == 0;
}

void Minion::Shoot(Vec2 target){
    float adjust;

    Vec2 minionPos;
    minionPos.x = associated.box.x;
    minionPos.y = associated.box.y;

    GameObject *go = new GameObject();
    go->box.x = minionPos.x ;
    go->box.y = minionPos.y ;
    
    if((target.x-minionPos.x) >= 0){
        adjust = 0;
    }else if((target.x-minionPos.x) <= 0){
        adjust = M_PI;
    }

    Bullet *bullet = new Bullet(*go,
                                atan((target.y-minionPos.y)/(target.x-minionPos.x))+adjust,
                                500,
                                10,
                                target.Dist2Dots(minionPos,target),
                                "assets/img/minionbullet2.png",
                                true,
                                3);

    go->AddComponent(bullet);
    State &state = Game::GetInstance().GetCurrentState();
    state.AddObject(go);
}

void Minion::NotifyCollision(GameObject &other){
        
}

