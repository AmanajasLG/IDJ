#include "../include/Sprite.h" 
#include "../include/Resources.h"
#include "../include/Game.h"
#include "../include/Camera.h"


/*
Seta texture como nullptr (imagem não carregada).
*/
Sprite::Sprite(GameObject &associeted) : Component(associeted){
    texture = nullptr;
}

/*
Seta texture como nullptr. Em seguida, chama Open.
*/
Sprite::Sprite(GameObject &associeted, string file) : Component(associeted){
    texture = nullptr;
    Open(file);
}

/*
Se houver imagem alocada, desaloca.
*/
Sprite::~Sprite(){

}

/*
Carrega a imagem indicada pelo caminho file.
*/
void Sprite::Open(string file){
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);

    SetClip(0,0,width,height);
}

/*
Seta clipRect com os parâmetros dados.
*/
void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.w = w;
    clipRect.h = h;
    clipRect.x = x;
    clipRect.y = y;
}

/*
Render é um wrapper para SDL_RenderCopy, que recebe quatro argumentos.
    ● SDL_Renderer* renderer: O renderizador de Game.
    ● SDL_Texture* texture: A textura a ser renderizada;
    ● SDL_Rect* srcrect: O retângulo de clipagem. Especifica uma área da textura a ser "recortada" e renderizada.
    ● SDL_Rect* dstrect: O retângulo destino. Determina a posição na tela em que a textura deve ser renderizada membros x e y). Se os membros w e h diferirem das dimensões do clip,causarão uma mudança na escala, contraindo ou expandindo a imagem para se adaptar a esses valores.
*/
void Sprite::Render(){
    //Sprite::Render(associated.box.x, associated.box.y);
    Sprite::Render(associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y);
}

void Sprite::Render(int x, int y){
    SDL_Rect dstrect;
    
    dstrect.x = x; 
    dstrect.y = y;
    dstrect.h = clipRect.h;
    dstrect.w = clipRect.w;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);   
}

/*
Retorna largura da imagem.
*/
int Sprite::GetWidth(){
    return width;
}

/*
Retorna altura da imagem.
*/
int Sprite::GetHeight(){
    return height;
}
    
/*
Retorna true se texture estive alocada.
*/
bool Sprite::IsOpen(){
    return texture != nullptr;
}

bool Sprite::Is(std::string type){
    return strcmp(type.c_str(),"Sprite") == 0;
}

void Sprite::Update(float dt){

}
