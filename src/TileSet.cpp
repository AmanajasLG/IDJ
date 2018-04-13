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
    cout<<columns<<endl;
    cout<<rows<<endl;
}

/*
    Checa se o índice é válido, para o número de tiles que temos, isto é,
    está entre 0 e o número de tiles - 1. Se sim, calcula e seta o clip desejado
    no sprite, e renderiza na posição dada.
*/
void TileSet::RenderTile(unsigned index, float x, float y){
    //cout<<index<< " "<< x <<" "<< y<<endl;
    unsigned numTiles = columns*rows;
    unsigned contIndex = 0;
    if(index <= (numTiles - 1)){
        for(int y2 = 0; y2 < tileSet->GetWidth(); y2 += tileWidth){
            for(int x2 = 0; x2 < tileSet->GetHeight(); x2 += tileHeight){
                if(contIndex == index){
                    tileSet->SetClip(x,y,tileWidth,tileHeight);
                    tileSet->Render(x2,y2);
                    cout<<index<< " "<< x2 <<" "<< y2 <<endl;
                }
                contIndex++;
            }
        }
    }
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}