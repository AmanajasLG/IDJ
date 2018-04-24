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
    Camera::speed.x = 5;
    Camera::speed.y = 5;

    if(InputManager::GetInstance().IsKeyDown(SDLK_UP) || InputManager::GetInstance().IsKeyDown(SDLK_w)){
        Camera::speed.y *= dt;
        Camera::pos.y += Camera::speed.y;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_DOWN) || InputManager::GetInstance().IsKeyDown(SDLK_s)){
        Camera::speed.y *= -dt;
        Camera::pos.y += Camera::speed.y;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT) || InputManager::GetInstance().IsKeyDown(SDLK_a)){
        Camera::speed.x *= dt;
        Camera::pos.x += Camera::speed.x;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT) || InputManager::GetInstance().IsKeyDown(SDLK_d)){
        Camera::speed.x *= -dt;
        Camera::pos.x += Camera::speed.x;
    }
}

