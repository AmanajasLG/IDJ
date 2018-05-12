#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Face.h"

GameObject *Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject *newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if(focus == nullptr){
        Camera::speed.x = 500;
        Camera::speed.y = 500;

        if(InputManager::GetInstance().IsKeyDown(SDLK_UP)){
            Camera::speed.y *= dt;
            Camera::pos.y += Camera::speed.y;
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_DOWN)){
            Camera::speed.y *= -dt;
            Camera::pos.y += Camera::speed.y;
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT)){
            Camera::speed.x *= dt;
            Camera::pos.x += Camera::speed.x;
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)){
            Camera::speed.x *= -dt;
            Camera::pos.x += Camera::speed.x;
        }
    }else{
        Camera::pos.x = - focus->box.x + 512 - focus->box.w/2;
        Camera::pos.y = - focus->box.y + 300 - focus->box.h/2;
    }
}