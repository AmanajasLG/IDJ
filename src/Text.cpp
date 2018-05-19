#include "../include/Text.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include "../include/Resources.h"

Text::Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated), text(text), style(style), fontFile(fontFile), fontSize(fontSize), color(color) {
    font = Resources::GetFont(fontFile,fontSize);
    
    int width;
    int height;
    TTF_SizeText(font,text.c_str(),&width,&height);
    associated.box.w = width;
    associated.box.h = height;
    
    
    texture = nullptr;
    timer = Timer(0.5);
    
    show = 0;

    RemakeTexture();
}

Text::~Text(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt){
    if(timer.Update(dt)){
        show = !show;
        timer.Restart();
    }
        
}

void Text::Render(){
    
    if(texture != nullptr && show){
        SDL_Rect cliprect, dstrect;

        cliprect.x = 0;
        cliprect.y = 0;
        cliprect.w = associated.box.w;
        cliprect.h = associated.box.h;

        dstrect.x = 512 - cliprect.w/2; 
        dstrect.y = 300 - cliprect.h/2; 
        dstrect.h = cliprect.h;
        dstrect.w = cliprect.w;

        SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &cliprect, &dstrect);
    }
    
}

bool Text::Is(std::string type){
    return strcmp(type.c_str(),"Text") == 0;
}

void Text::RemakeTexture(){
    SDL_Surface *surface;

    if(style == TextStyle::BLENDED){
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
    }else if(style == TextStyle::SHADED){
        surface = TTF_RenderText_Shaded(font, text.c_str(), color, color);
    }else{
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
    }

    surface->w = associated.box.w;
    surface->h = associated.box.h;
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);    

    SDL_FreeSurface(surface);
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile){
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style){
    this->style = style;
    RemakeTexture();
}