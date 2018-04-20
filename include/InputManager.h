#pragma once 
#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define INCLUDE_SDL
#include "../include/SDL_include.h"
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

/*
    InputManager é um singleton que lê a pilha de eventos sempre que seu método
    Update é chamado (no início de cada frame).
*/
class InputManager{
private:
    bool mouseState[6];
    int mouseUpdate[6];
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    bool quitRequest;
    int updateCounter;
    int mouseX;
    int mouseY;

    InputManager();

    ~InputManager();

public:
    void Update();

    bool KeyPressed(int key);

    bool KeyRelease(int key);

    bool IsKeyDown(int key);

    bool MousePressed(int button);

    bool MouseRelease(int button);

    bool IsMouseDown(int button);

    int GetMouseX();

    int GetMouseY();

    bool QuitRequested();

    static InputManager &GetInstance();
};