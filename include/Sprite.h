#pragma once 
#define INCLUDE_SDL_IMAGE
#include "../include/SDL_include.h"
#include "../include/Component.h"
#include "../include/Timer.h"
#include <iostream>
#include <string>
using namespace std;

/*
A classe Sprite encapsula o carregamento e uso de SDL_Textures, o tipo da SDL que contém uma imagem carregada do disco pronta para ser renderizada num SDL_Renderer.
*/
class Sprite : public Component{
private:
    SDL_Texture *texture;   //imagem 
    int width;              //dimensão largura
    int height;             //dimensão altura
    SDL_Rect clipRect;      //retangulo de clipping
    Vec2 scale;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    Timer timer;
    

public:
    float arc;

    Sprite(GameObject &associeted, int frameCount = 1, float frameTime = 1, float timeMax = 0);

    Sprite(GameObject &associeted,std::string file, int frameCount = 1, float frameTime = 1, float timeMax = 0);

    ~Sprite();

    void Open(string file);

    void SetClip(int x, int y, int w, int h);

    int GetWidth();

    int GetHeight();
    
    void Render();

    void Render(int mouseX, int mouseY);

    bool Is(std::string type);

    void Update(float dt);

    bool IsOpen();

    void SetScale(float scaleX, float scaleY);

    Vec2 GetScale();

    void SetFrame(int frame);

    void SetFrameCount(int frameCount);

    void SetFrameTime(float frameTime);

    void NotifyCollision(GameObject &other);
};
