#include "../include/Resources.h"
#include "../include/Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file){
    SDL_Texture *texture;
    if(imageTable.empty()){
        
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

        if(texture == nullptr){
            cout<< "Erro ao criar textura empty!" <<endl;
            cout<< "ERRO: " << SDL_GetError() <<endl;
            return nullptr;
        }


        imageTable.emplace(file, texture);

        return texture;
    }

    std::unordered_map<std::string, SDL_Texture*>::const_iterator got = imageTable.find(file);
    if(got == imageTable.end()){
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

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
    Mix_Music *music;
    if(musicTable.empty()){
        music = Mix_LoadMUS(file.c_str());
        
        if(music == nullptr){
            std::cout<< "Erro! Musica não foi encontrada!" <<endl; 
            return nullptr;
        }

        musicTable.emplace(file, music);
        
        return music;
    }
    
    std::unordered_map<std::string, Mix_Music*>::const_iterator got = musicTable.find(file);
    if(got == musicTable.end()){
        music = Mix_LoadMUS(file.c_str());

        if(music == nullptr){
            std::cout<< "Erro! Musica não foi encontrada!" <<endl; 
            return nullptr;
        }


        musicTable.emplace(file, music);

        return music;        
    }

    return got->second;    
}

void Resources::ClearMusics(){
    
    for(auto& i : musicTable){
        Mix_FreeMusic(i.second);        
    }

    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file){
    Mix_Chunk *chunk;
    if(soundTable.empty()){
        chunk = Mix_LoadWAV(file.c_str());

        if(chunk == nullptr){
            std::cout<< "Erro! Som não foi encontrado!" <<endl;
            return nullptr; 
        }


        soundTable.emplace(file, chunk);

        return chunk;
    }
    std::unordered_map<std::string, Mix_Chunk*>::const_iterator got = soundTable.find(file);
    if(got == soundTable.end()){
        chunk = Mix_LoadWAV(file.c_str());

        if(chunk == nullptr){
            std::cout<< "Erro! Som não foi encontrado!" <<endl;
            return nullptr; 
        }


        soundTable.emplace(file, chunk);

        return chunk;
    }

    return got->second;
}

void Resources::ClearSounds(){
    for(auto& i : soundTable){
        Mix_FreeChunk(i.second);        
    }

    soundTable.clear();
}