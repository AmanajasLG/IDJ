#include "../include/InputManager.h"

/*
    Construtor inicializa os arrays de estado e update do mouse
    assim como as demais variáveis.
*/
InputManager::InputManager(){
    mouseState[5] = {false};
    mouseUpdate[5] = {0};
    mouseX = 0;
    mouseY = 0;
    updateCounter = 0;
    quitRequest = false;
}

InputManager::~InputManager(){
    
}

/* 
    Ao invés de dar um new InputManager na primeira vez que a função
    é chamada, GetInstance declara dentro dela uma variável InputManager 
    estática que é retornada (Meyers’ Singleton).
*/
InputManager &InputManager::GetInstance(){
    static InputManager instance;

    return instance;
}

/*
    GetMuoseX, GetMouseY e QuitRequest retornam os valores de suas
    respectivas variáveis.
*/
int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequest;
}

/*
    ___Press e ___Release verificam o pressionamento ocorrido naquele frame, 
    e só retornam true nesse caso. Is___Down retorna se o botão/tecla
    está pressionado, independente de quando isso ocorreu.
*/
bool InputManager::KeyPressed(int key){
    std::unordered_map<int,int>::const_iterator got = keyUpdate.find(key);
    if(got == keyUpdate.end()){
        return false;
    }
    if(got->second == updateCounter){
        return keyState[key];
    }
    
    return false;
}

bool InputManager::KeyRelease(int key){
    std::unordered_map<int,int>::const_iterator got = keyUpdate.find(key);
    if(got == keyUpdate.end()){
        return false;
    }
    if(got->second == updateCounter){
        return !keyState[key];
    }        
    
    return false;
}

bool InputManager::IsKeyDown(int key){
    std::unordered_map<int,bool>::const_iterator got = keyState.find(key);
    if(got == keyState.end()){
        return false;
    }
    return keyState[key];
}

bool InputManager::MousePressed(int button){
    if(mouseUpdate[button] == updateCounter)
        return mouseState[button];

    return false;
}

bool InputManager::MouseRelease(int button){
    if(mouseUpdate[button] == updateCounter)
        return !mouseState[button];

    return false;
}

bool InputManager::IsMouseDown(int button){
    return mouseState[button];
}

/*
    Update faz o processamento de eventos.
*/
void InputManager::Update(){
    SDL_Event event;
    SDL_GetMouseState(&mouseX,&mouseY);
    
    updateCounter++;
    quitRequest = false;

    while(SDL_PollEvent(&event)){
          
        switch(event.type){
        case SDL_KEYDOWN:
            if(event.key.repeat)
                continue;
            
            keyState[event.key.keysym.sym] = true;
            keyUpdate[event.key.keysym.sym] = updateCounter;           
            break;

        case SDL_KEYUP:
            keyState[event.key.keysym.sym] = false;
            keyUpdate[event.key.keysym.sym] = updateCounter;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_QUIT:
            quitRequest = true;
            break;
        default:
            break;
        }
              
    }
}