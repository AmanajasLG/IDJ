#include "../include/Sprite.h" 
#include "../include/Game.h"

Game game = Game::GetInstance();

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
    if(IsOpen()){
        SDL_DestroyTexture(texture);
    }    
}

/*
Carrega a imagem indicada pelo caminho file.
*/
void Sprite::Open(string file){
    if(IsOpen() == true){
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(game.GetRenderer(),file.c_str());
    if(texture == nullptr){
        cout<< "Erro ao criar textura!" <<endl;
        cout<< "ERRO: " << SDL_GetError() <<endl;
        return;
    }

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
    SDL_Rect dstrect;
    
    dstrect.x = associeted.box.x; 
    dstrect.y = associeted.box.y;
    dstrect.h = clipRect.h;
    dstrect.w = clipRect.w;

    SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dstrect);
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
    if(texture != nullptr){
        return true;
    }
    return false;
}

bool Sprite::Is(std::string type){
    if(strcmp(type.c_str(),"Sprite") == 0){
        return true;
    }
    return false;
}

void Sprite::Update(float dt){

}