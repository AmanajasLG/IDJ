#include "../include/PenguinBody.h"
#include "../include/PenguinCannon.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/Vec2.h"
#include "../include/State.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/Bullet.h"

PenguinBody *PenguinBody::player;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated){
    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    hp = 100;
    linearSpeed = 0;
    angle = 0;
    speed.x = linearSpeed * cos(angle);
    speed.y = linearSpeed * sin(angle);
}

PenguinBody::~PenguinBody(){
    player = nullptr;
}

void PenguinBody::Start(){
    State &state = Game::GetInstance().GetState();

    GameObject *go = new GameObject();
    PenguinCannon *penguinCannon = new PenguinCannon(*go,state.GetObjectPtr(&associated));
    go->AddComponent(penguinCannon);

    pcannon = state.AddObject(go);       
}

void PenguinBody::Update(float dt){
    
    if(InputManager::GetInstance().IsKeyDown(SDLK_a)){
        angle -= dt;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_d)){
        angle += dt;
    }

    Sprite *sprite = (Sprite*)associated.GetComponent("Sprite");
    sprite->arc = angle;
    
    if(InputManager::GetInstance().IsKeyDown(SDLK_w)){
        if(linearSpeed < 100){
            linearSpeed += dt*10;
        }
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_s)){
        if(linearSpeed > -100){
            linearSpeed -= dt*10;
        }
    }

    speed.x = linearSpeed * cos(angle);
    speed.y = linearSpeed * sin(angle);

    associated.box.x += speed.x;
    associated.box.y += speed.y;

    if(hp <= 0){
        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
    }
    
}

void PenguinBody::Render(){

}

bool PenguinBody::Is(std::string type){
    return strcmp(type.c_str(),"PenguinBody") == 0;
}

void PenguinBody::NotifyCollision(GameObject &other){
    Bullet *bullet = (Bullet*)other.GetComponent("Bullet");
    if(bullet != nullptr && bullet->targetsPlayer){
        hp -= bullet->GetDamage();
        if(hp <= 0){
            Camera::Unfollow();
            Sprite* spriteB = (Sprite*)associated.GetComponent("Sprite");
            associated.RemoveComponent(spriteB);
            
            GameObject *go = new GameObject();
            Sprite *sprite = new Sprite(*go,"assets/img/penguindeath.png",5,0.2,1);
            go->box.w = sprite->GetWidth();
            go->box.h = sprite->GetHeight();
            go->box.x = associated.box.x ;
            go->box.y = associated.box.y ;
            go->AddComponent(sprite);

            State &state = Game::GetInstance().GetState();
            state.AddObject(go);

            associated.RequestDelete();
        }
    }
    cout<<"COLISION PENGUIN HP = "<<hp<<endl;
}

Vec2 PenguinBody::GetPos(){    
    return Vec2(associated.box.x,associated.box.y);
}