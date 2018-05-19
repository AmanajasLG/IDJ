#pragma once 
#define INCLUDE_SDL_TTF
#include "../include/SDL_include.h"
#include "../include/Component.h"
#include "../include/Timer.h"

class Text : public Component{
public:
    enum TextStyle{SOLID,SHADED,BLENDED};

    Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);

    ~Text();

    void Update(float dt); 

    void Render();

    bool Is(std::string type);

    void SetText(std::string text);

    void SetColor(SDL_Color color);

    void SetStyle(TextStyle style);

    void SetFontSize(int fontSize);

    void SetFontFile(std::string fontFile);
private:
    TTF_Font *font = nullptr;
    SDL_Texture *texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
    Timer timer;
    int show;

    void RemakeTexture();
};
