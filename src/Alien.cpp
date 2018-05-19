#include "../include/Alien.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Minion.h"
#include "../include/State.h"
#include "../include/Collider.h"
#include "../include/Bullet.h"
#include "../include/PenguinBody.h"

Alien::Alien(GameObject &associated, int nMinions, float timeOffset) : Component (associated) {
    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

    alienCount++;
    state = AlienState::RESTING;
    restTimer = Timer(timeOffset);

    hp = 100;
    speed.x = 0;
    speed.y = 0;

    minionArray.resize(nMinions);
}

void Alien::Start(){
    State &state = Game::GetInstance().GetCurrentState();
    
    std::weak_ptr<GameObject> weakGO(state.GetObjectPtr(&associated));
    for(int i = 0; i < minionArray.size(); i++){
        GameObject *go = new GameObject();
        Minion *minion = new Minion(*go, weakGO, (i*2) *  M_PI/minionArray.size());
        go->AddComponent(minion);
        minionArray[i] = state.AddObject(go);
    }
    
}

Alien::~Alien(){

    for(auto& m : minionArray){
        m.lock()->RequestDelete();
      
    }

    minionArray.clear();

    alienCount--;
}

void Alien::Update(float dt){
    Sprite *sprite = (Sprite*) associated.GetComponent("Sprite");
    sprite->arc += dt;

    if(PenguinBody::player == nullptr)
        return;
    
    if(state == AlienState::RESTING){
        if(restTimer.Update(dt)){
            state = AlienState::MOVING;
            destination = PenguinBody::player->GetPos();
           
        }
        
    }else{
        
        Vec2 normalize;
        normalize.x = - associated.box.x + destination.x - associated.box.w/2;
        normalize.y = - associated.box.y + destination.y - associated.box.h/2;

        if((int)normalize.x == 0 && (int)normalize.y == 0 ){
            Minion *minion = (Minion*)minionArray[ClosestMinion(PenguinBody::player->GetPos())].lock()->GetComponent("Minion");
            minion->Shoot(PenguinBody::player->GetPos());
            state = AlienState::RESTING;
            restTimer.Restart();            
        }else{
            speed.NormalizeVec(&normalize);
            
            
            speed.x = normalize.x * 10;
            speed.y = normalize.y * 10;

            if(abs(-(int)associated.box.x + (int)destination.x - (int)associated.box.w/2) < abs((int)speed.x)){
                associated.box.x = - associated.box.w/2 + destination.x;
            }else if(speed.x != 0){
                
                associated.box.x += (int)speed.x;
            }

            if(abs(-(int)associated.box.y + (int)destination.y - (int)associated.box.h/2) < abs((int)speed.y)){
                associated.box.y = - associated.box.h/2 + destination.y;
            }else if(speed.y != 0){
                associated.box.y += (int)speed.y;
            }
        }

    }


}

void Alien::Render(){

}
 
bool Alien::Is(std::string type){
    return strcmp(type.c_str(),"Alien") == 0;
}
 
int Alien::ClosestMinion(Vec2 target){
    int closer = 0;
    float distMin = INTMAX_MAX; 
    Vec2 minionPos;

    for(int i = 0; i < minionArray.size(); i++){
        minionPos.x = minionArray[i].lock()->box.x;
        minionPos.y = minionArray[i].lock()->box.y;    
        if(minionPos.Dist2Dots(minionPos,target) < distMin){
            closer = i;
            distMin = minionPos.Dist2Dots(minionPos,target);
        } 
    }

    return closer;
}

void Alien::NotifyCollision(GameObject &other){
    Bullet *bullet = (Bullet*)other.GetComponent("Bullet");
    if(bullet != nullptr && !bullet->targetsPlayer){
        hp -= bullet->GetDamage();
        if(hp <= 0){
            Sprite* spriteA = (Sprite*)associated.GetComponent("Sprite");
            associated.RemoveComponent(spriteA);

            GameObject *go = new GameObject();
            Sprite *sprite = new Sprite(*go,"assets/img/aliendeath.png",4,0.2,1);
            go->box.w = sprite->GetWidth();
            go->box.h = sprite->GetHeight();
            go->box.x = associated.box.x + go->box.w/4;
            go->box.y = associated.box.y + go->box.h/4;
        
            go->AddComponent(sprite);

            State &state = Game::GetInstance().GetCurrentState();
            state.AddObject(go);

            associated.RequestDelete();

            for(auto& m : minionArray){
                Sprite *spriteM = (Sprite*)m.lock()->GetComponent("Sprite");
                m.lock()->RemoveComponent(spriteM);

                GameObject *go = new GameObject();
                Sprite *sprite = new Sprite(*go,"assets/img/miniondeath.png",4,0.2,1);
                go->box.w = sprite->GetWidth();
                go->box.h = sprite->GetHeight();
                go->box.x = m.lock()->box.x + go->box.w/2;
                go->box.y = m.lock()->box.y + go->box.h/2;
                go->AddComponent(sprite);

                State &state = Game::GetInstance().GetCurrentState();
                state.AddObject(go);
            }
        }
    }
}

int Alien::GetHP(){
    return hp;
}