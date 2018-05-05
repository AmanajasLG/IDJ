#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include <math.h>

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter){
    arc = arcOffsetDeg;

    Sprite *sprite = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(sprite);

    std::shared_ptr<GameObject> sharedGO(this->alienCenter.lock());

    associated.box.h = sprite->GetHeight();
    associated.box.w = sprite->GetWidth();
    associated.box.x = sharedGO->box.x;
    associated.box.y = sharedGO->box.y;
    
}

void Minion::Update(float dt){
    Vec2 minionPos = Vec2(200, 0);

    std::shared_ptr<GameObject> sharedGO(alienCenter.lock());

    if(sharedGO == nullptr){
        cout<<"MINION ALIENCENTER NULL!"<<endl;
        return;
    }
    arc += dt;
    minionPos.GetRotated(arc);

    Vec2 objPos = objPos.AddVectors(minionPos, Vec2( sharedGO->box.x  + sharedGO->box.w/4, sharedGO->box.y  + sharedGO->box.h/4));
    associated.box.x = objPos.x;
    associated.box.y = objPos.y;
}

void Minion::Render(){

}

bool Minion::Is(std::string type){
    return strcmp(type.c_str(),"Minion") == 0;
}

void Minion::Shoot(Vec2 target){
    Vec2 minionPos;
    minionPos.x = associated.box.x;
    minionPos.y = associated.box.y;

    GameObject *go = new GameObject();
    go->box.x = minionPos.x;
    go->box.y = minionPos.y;

    std::cout<< "MINIONPOS X = " <<minionPos.x <<endl;
    std::cout<< "MINIONPOS Y = " <<minionPos.y <<endl;
    std::cout<< "TARGET X = " <<target.x <<endl;
    std::cout<< "TARGET Y = " <<target.y <<endl;

    Bullet *bullet = new Bullet(*go,
                                atan((target.y-minionPos.y)/(target.x-minionPos.x)),
                                20,
                                10,
                                target.Dist2Dots(target, minionPos),
                                "assets/img/minionbullet1.png");

    go->AddComponent(bullet);
    State &state = Game::GetInstance().GetState();
    state.AddObject(go);
}