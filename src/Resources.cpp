#include "../include/Resources.h"

Game game = Game::GetInstance();
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file){
    std::unordered_map<std::string, SDL_Texture*>::const_iterator got = imageTable.find(file);
    if(got == imageTable.end()){
        SDL_Texture *texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());

        if(texture == nullptr){
            cout<< "Erro ao criar textura!" <<endl;
            cout<< "ERRO: " << SDL_GetError() <<endl;
            return nullptr;
        }


        imageTable.emplace(file, texture);

        return texture;
    }

    return got->second;
    
}

void Resources::ClearImages(){
    for(auto& i : imageTable){
        SDL_DestroyTexture(i.second);        
    }

    imageTable.clear();
}

Mix_Music *Resources::GetMusic(std::string file){
    std::unordered_map<std::string, Mix_Music*>::const_iterator got = musicTable.find(file);
    if(got != musicTable.end()){
        return got->second;
    }

    Mix_Music *music = Mix_LoadMUS(file.c_str());

    if(music == nullptr){
        std::cout<< "Erro! Musica não foi encontrada!" <<endl; 
        return nullptr;
    }


    musicTable.emplace(file, music);

    return music;
}

void Resources::ClearMusics(){
    for(auto& i : musicTable){
        Mix_FreeMusic(i.second);        
    }

    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file){
    std::unordered_map<std::string, Mix_Chunk*>::const_iterator got = soundTable.find(file);
    if(got != soundTable.end()){
        return got->second;
    }

    Mix_Chunk *chunk = Mix_LoadWAV(file.c_str());

    if(chunk == nullptr){
        std::cout<< "Erro! Som não foi encontrado!" <<endl;
        return nullptr; 
    }


    soundTable.emplace(file, chunk);

    return chunk;
}

void Resources::ClearSounds(){
    for(auto& i : soundTable){
        Mix_FreeChunk(i.second);        
    }

    soundTable.clear();
}