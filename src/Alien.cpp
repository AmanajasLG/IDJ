#include "../include/Alien.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Minion.h"
#include "../include/State.h"

Alien::Alien(GameObject &associated, int nMinions) : Component (associated) {
    Sprite *sprite = new Sprite(associated);

    associated.AddComponent(sprite);

    hp = 50;
    speed.x = 0;
    speed.y = 0;

    minionArray.resize(nMinions);

    arc = 0;
}

void Alien::Start(){
    State &state = Game::GetInstance().GetState();
    
    std::weak_ptr<GameObject> weakGO(state.GetObjectPtr(&associated));
    for(int i = 0; i < minionArray.size(); i++){
        GameObject *go = new GameObject();
        Minion *minion = new Minion(*go, weakGO, (i*2) *  M_PI/minionArray.size());
        go->AddComponent(minion);
        minionArray[i] = state.AddObject(go);
    }
    
}

Alien::~Alien(){
    for(int i = 0; i < minionArray.size(); i++){
        minionArray.pop_back();        
    }
}

Alien::Action::Action(ActionType type, float x, float y):
type(type){
    pos.x = x;
    pos.y = y;
}

void Alien::Update(float dt){
    if(InputManager::GetInstance().MousePressed(LEFT_MOUSE_BUTTON)){
        Alien::Action action = Alien::Action(Action::ActionType::SHOOT , InputManager::GetInstance().GetMouseX() - Camera::pos.x,InputManager::GetInstance().GetMouseY() - Camera::pos.y);
        taskQueue.emplace(action);
    }

    if(InputManager::GetInstance().MousePressed(RIGHT_MOUSE_BUTTON)){
        Alien::Action action = Alien::Action(Action::ActionType::MOVE , InputManager::GetInstance().GetMouseX() - Camera::pos.x,InputManager::GetInstance().GetMouseY() - Camera::pos.y);
        taskQueue.emplace(action);
    }  

    if(taskQueue.empty())
        return;

    
    if(taskQueue.front().type == Action::ActionType::MOVE){       
        Vec2 normalize;
        normalize.x = - associated.box.x + taskQueue.front().pos.x - associated.box.w/2;
        normalize.y = - associated.box.y + taskQueue.front().pos.y - associated.box.h/2;

        if(normalize.x == 0 && normalize.y == 0 ){
            taskQueue.pop();
        }else{
            speed.NormalizeVec(&normalize);
            
            
            speed.x = normalize.x * 10;
            speed.y = normalize.y * 10;

            if(abs(-(int)associated.box.x + (int)taskQueue.front().pos.x - (int)associated.box.w/2) < abs((int)speed.x)){
                associated.box.x = - associated.box.w/2 + taskQueue.front().pos.x;
            }else if(speed.x != 0){
                
                associated.box.x += (int)speed.x;
            }

            if(abs(-(int)associated.box.y + (int)taskQueue.front().pos.y - (int)associated.box.h/2) < abs((int)speed.y)){
                associated.box.y = - associated.box.h/2 + taskQueue.front().pos.y;
            }else if(speed.y != 0){
                associated.box.y += (int)speed.y;
            }
                
            if(abs(-(int)associated.box.x + (int)taskQueue.front().pos.x - (int)associated.box.w/2) < abs((int)speed.x) && abs(-(int)associated.box.y + (int)taskQueue.front().pos.y - (int)associated.box.h/2) < abs((int)speed.y)){
                taskQueue.pop();
            }
        }

        
    }else {
        Minion *minion = (Minion*)minionArray[ClosestMinion()].lock()->GetComponent("Minion");
        minion->Shoot(taskQueue.front().pos);
        taskQueue.pop();
    }
    


}

void Alien::Render(){

}

bool Alien::Is(std::string type){
    if(strcmp(type.c_str(),"Alien") == 0){
        return true;
    }
    return false;
}

int Alien::ClosestMinion(){
    int closer = 0;
    float distMin = INTMAX_MAX; 
    Vec2 minionPos;

    for(int i = 0; i < minionArray.size(); i++){
        minionPos.x = minionArray[i].lock()->box.x;
        minionPos.y = minionArray[i].lock()->box.y;    
        if(minionPos.Dist2Dots(minionPos,taskQueue.front().pos) < distMin){
            closer = i;
            distMin = minionPos.Dist2Dots(minionPos,taskQueue.front().pos);
        } 
    }

    return closer;
}