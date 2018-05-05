#include "../include/Sound.h"
#include "../include/Resources.h"

Sound::Sound(GameObject &associeted) : Component (associeted){
    chunk = nullptr;
}

Sound::Sound(GameObject &associeted, std::string file) : Sound::Sound(associeted){
    Open(file);
}

Sound::~Sound(){
    if(chunk != nullptr){
        Mix_HaltChannel(channel);
    }
}

void Sound::Play(int times){
    if(chunk == nullptr){
        std::cout<< "Erro ao tocar musica! Não há musica iniciada!" <<endl;
        return;
    }
    
    channel = Mix_PlayChannel(-1,chunk,times);
}

void Sound::Stop(){
    if(chunk != nullptr){
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file){
    chunk = Resources::GetSound(file);
}

void Sound::Update(float dt){

}

void Sound::Render(){

}

bool Sound::Is(std::string type){
    return strcmp(type.c_str(),"Sound") == 0;
}

bool Sound::SoundIsPlaying(){
    return Mix_Playing(channel);
}