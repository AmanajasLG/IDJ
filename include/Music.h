#pragma once 
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>
#include <string>
using namespace std;

/*
Music “abre” um arquivo de música e o reproduz quando pedido.
*/
class Music {
private:
    Mix_Music *music;

public:
    Music();

    Music(std::string file);

    ~Music();

    void Play(int times = -1);

    void Stop(int msToStop = 1500);

    void Open(std::string file);

    bool IsOpen();
};
