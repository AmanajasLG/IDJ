#include"../include/TileSet.h"

/*
    Seta as dimensões dos tiles e abre o Sprite. Se a abertura for bem
    sucedida, descobre, pelo tamanho do sprite e dos tiles, quantas colunas e
    quantas linhas o tileset tem.
*/
TileSet::TileSet(int tileWidth, int tileHeight, std::string file) :
tileHeight(tileHeight), tileWidth(tileWidth)
{
    GameObject *tiles = new GameObject();
    tileSet = new Sprite(*tiles,file);

    if(tileSet == nullptr){
        std::cout<<"Não foi possivel inicializar sprite tileSet!"<<endl;
        return;
    }

    columns = tileSet->GetWidth()/tileWidth;
    rows = tileSet->GetHeight()/tileHeight;
}

/*
    Checa se o índice é válido, para o número de tiles que temos, isto é,
    está entre 0 e o número de tiles - 1. Se sim, calcula e seta o clip desejado
    no sprite, e renderiza na posição dada.
*/
void TileSet::RenderTile(unsigned index, float x, float y){
    int x2 = (index%columns)*tileWidth;
    int y2 = (index/columns)*tileHeight;

    tileSet->SetClip(x2,y2,tileWidth,tileHeight);
    tileSet->Render(x,y);
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}