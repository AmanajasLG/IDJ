#pragma once 
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/Component.h"
#include <iostream>
#include <string>
using namespace std;

/*
Sound é quase a mesma classe de Music, mesmo na implementação. 
As diferenças estão nas funções da Mixer usadas, e no fato de 
que, diferente das músicas, existem vários canais diferentes 
para reproduzir sons, e temos que manter registrado em qual 
canal o chunk está tocando para podermos pará-lo se necessário.
*/
class Sound : public Component{
private:
    Mix_Chunk *chunk;
    int channel = -1;

public:
    Sound(GameObject &associeted);

    Sound(GameObject &associeted, std::string file);

    ~Sound();

    void Play(int times = 0);   //times = 0 porque quando coloquei como 1 ele repetiu

    void Stop();

    void Open(std::string file);

    bool IsOpen();

    void Update(float dt);

    void Render();

    bool Is(std::string type);
};