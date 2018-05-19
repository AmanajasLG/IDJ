#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include <iostream>
#include <unordered_map>
#include <string>

class Resources{
private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
    static std::unordered_map<std::string, TTF_Font*> fontTable;

public:
    static SDL_Texture *GetImage(std::string file);

    static void ClearImages();

    static Mix_Music *GetMusic(std::string file);

    static void ClearMusics();

    static Mix_Chunk *GetSound(std::string file);

    static void ClearSounds();

    static TTF_Font *GetFont(std::string file, int ptsize);

    static void ClearFonts();

    
};