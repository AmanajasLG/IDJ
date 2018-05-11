#include "../include/PenguinBody.h"
#include "../include/PenguinCannon.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/Camera.h"
#include "../include/Collider.h"
#include "../include/Timer.h"

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody) : Component(associated){
    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    //timer = Timer();

    pbody = penguinBody;
    angle = 0;

    Sprite *sprite = new Sprite(associated,"assets/img/cubngun.png");
    sprite->arc = angle;
    associated.AddComponent(sprite);   

    associated.box.w = sprite->GetWidth();
    associated.box.h = sprite->GetHeight();
    associated.box.x = pbody.lock()->box.x + associated.box.w/2;
    associated.box.y = pbody.lock()->box.y + associated.box.h/2; 
    
}

void PenguinCannon::Update(float dt){
    timer.Update(dt);
    cout<<"CARALHO"<<endl;
    if(pbody.lock() == nullptr){
        cout<<"PORRE"<<endl;
        Sprite* spriteC = (Sprite*)associated.GetComponent("Sprite");
        associated.RemoveComponent(spriteC);
        associated.RequestDelete();
        return;
    }
    cout<<"FDP"<<endl;
    associated.box.x = pbody.lock()->box.x + (pbody.lock()->box.w/2 - associated.box.w/2);
    associated.box.y = pbody.lock()->box.y + (pbody.lock()->box.h/2 - associated.box.h/2);

    float adjust; 

    if((InputManager::GetInstance().GetMouseX()-Camera::pos.x-associated.box.x) >= 0){
        adjust = 0;
    }else if((InputManager::GetInstance().GetMouseX()-Camera::pos.x-associated.box.x) <= 0){
        adjust = M_PI;
    }

    angle = atan((InputManager::GetInstance().GetMouseY()-Camera::pos.y-associated.box.y)/(InputManager::GetInstance().GetMouseX()-Camera::pos.x-associated.box.x))+adjust;
    
    //atan((InputManager::GetInstance().GetMouseY()-associated.box.y)/(InputManager::GetInstance().GetMouseX()-associated.box.x))+adjust; 
    //Sprite *sprite = (Sprite*)pbody.lock()->GetComponent("Sprite");
    //angle = sprite->arc; 

    Sprite *spritePC = (Sprite*)associated.GetComponent("Sprite");
    spritePC->arc = angle;

    if(InputManager::GetInstance().MousePressed(LEFT_MOUSE_BUTTON)){
        if(timer.Get() > 1){
            Shoot();
            timer.Restart(); 
        }
    }
    
}

void PenguinCannon::Render(){

}

bool PenguinCannon::Is(std::string type){
    return strcmp(type.c_str(),"PenguinCannon") == 0;
}

void PenguinCannon::Shoot(){
    GameObject *go = new GameObject();
    go->box.x = associated.box.x + associated.box.w/2 - 15; //- associated.box.w/2 * cos(angle);
    go->box.y = associated.box.y + associated.box.h/2 - 15; //- associated.box.y/2 * sin(angle);

    Vec2 bulletPos = Vec2(associated.box.w/2, 0);

    bulletPos.GetRotated(angle);
    
    Vec2 objPos = objPos.AddVectors(bulletPos, Vec2( go->box.x,go->box.y));
    go->box.x = objPos.x;
    go->box.y = objPos.y;

    Vec2 target;

    target.x = InputManager::GetInstance().GetMouseX()-Camera::pos.x;
    target.y = InputManager::GetInstance().GetMouseY()-Camera::pos.y;

    Vec2 cannonPos;

    cannonPos.x = go->box.x;
    cannonPos.y = go->box.y;

    Bullet *bullet = new Bullet(*go,
                                angle,
                                500,
                                10,
                                target.Dist2Dots(cannonPos,target),
                                "assets/img/penguinbullet.png",
                                4);

    go->AddComponent(bullet);
    State &state = Game::GetInstance().GetState();
    state.AddObject(go);
}

void PenguinCannon::NotifyCollision(GameObject &other){
    
}