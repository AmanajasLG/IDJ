#include "../include/TileMap.h"
#include <fstream>
#include <math.h>

/*
    Chama Load com a string passada e seta o tileset.
*/
TileMap::TileMap(GameObject &associetated, std::string file, TileSet *tileSet) : 
Component(associetated), tileSet(tileSet)  
{
    Load(file);
}

/*
    Load deve carregar um arquivo de mapa, no formato dado pelo arquivo
    map/tileMap.txt. Os primeiros três números são as dimensões do mapa: 
    largura, altura e profundidade. Em seguida, vêm os tiles, que devem 
    ser carregados em ordem para a matriz de tiles.
*/
void TileMap::Load(std::string file){
    std::ifstream tileMapFile;
    tileMapFile.open(file);
    

    if (!tileMapFile.is_open()){
        std::cout<<"Erro ao abrir o arquivo texto para TileMap!!"<<endl;
        return;
    }

    tileMapFile >> mapWidth;
    tileMapFile.get();
    tileMapFile >> mapHeight;
    tileMapFile.get();
    tileMapFile >> mapDepth;
    tileMapFile.get();
    
    
    int i = 0;
    int val;
    while(tileMapFile >> val){
        tileMatrix.emplace_back(val);
        
        // Tile vazio é representado por -1 ao invés de 0 como ta no arquivo
        tileMatrix[i]--;
        
        i++;
        tileMapFile.get();
    }
    tileMapFile.close();
}

/*
    Troca o tileSet em uso.
*/
void TileMap::SetTileSet(TileSet *tileSet){
    this->tileSet = tileSet;
}


/*
    Retorna uma referência ao elemento [x][y][z] de tileMatrix.
*/
int TileMap::At(int x, int y, int z){    
    int matrix = GetHeight()*GetWidth();
    return tileMatrix[z*matrix + x + y*GetWidth()];

}

/*
    Renderiza uma camada do mapa, tile a tile. 
    Dois ajustes a se fazer:
        ● Deve-se compensar o deslocamento da câmera;
        ● Deve-se considerar o tamanho de cada tile (use os membros
        GetTileWidth() e GetTileHeight() de TileSet);
*/
void TileMap::RenderLayer(int layer, int cameraX, int cameraY){    
    int x = cameraX; 
    int y = cameraY;
    int valPos;

    for(int posY = 0; posY < GetHeight(); posY++){
        for(int posX = 0; posX < GetWidth(); posX++){
            valPos = At(posX,posY,layer);
            if(valPos>=0){
                tileSet->RenderTile(valPos, x, y);
            }
            x+=tileSet->GetTileWidth();   
        }
        x = cameraX;
        y+= tileSet->GetTileHeight();
    }
}

/*
    Renderiza as camadas do mapa.
*/
void TileMap::Render(){
    for(int layer = 0; layer < mapDepth; layer++){
        RenderLayer(layer, associated.box.x*ParallaxScrolling(layer),associated.box.y*ParallaxScrolling(layer));
    }
    
}

int TileMap::ParallaxScrolling(int val){
    return (val + 1);
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}

void TileMap::Update(float dt){
    
}

bool TileMap::Is(std::string type){
    return strcmp(type.c_str(),"TileMap") == 0;
}