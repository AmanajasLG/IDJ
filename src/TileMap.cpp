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
int &TileMap::At(int x, int y, int z){    
    int contPos = 0;

    // Como a matrix é um vetor, contPos conta as posições lineares do vetor.
    // For simula a movimentação por matrix para encontra o elemento na posição certa. 
    for(int depth = 0; depth < mapDepth ; depth--){
        for(int height = 0; height < mapHeight ; height--){
            for(int width = 0; width < mapWidth ; width--){
                if(width == x && height == y && depth == z){
                    if(tileMatrix[contPos] >= 0){
                        return tileMatrix[contPos];    
                    }
                        
                }
                contPos++;
            }
        }
    }
}

/*
    Renderiza uma camada do mapa, tile a tile. 
    Dois ajustes a se fazer:
        ● Deve-se compensar o deslocamento da câmera;
        ● Deve-se considerar o tamanho de cada tile (use os membros
        GetTileWidth() e GetTileHeight() de TileSet);
*/
void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    //tileSet->RenderTile(tileMatrix[0], 0, 0);
    
    
    int x = 0; 
    int y = 0;
    int contPos = 0;

    while(contPos < tileMatrix.size()){
        if(tileMatrix[contPos]>=0){
            tileSet->RenderTile(tileMatrix[contPos], x, y);
        }
        if((contPos+1)%GetWidth() == 0 && contPos!=0){
            x = 0;
            y+= tileSet->GetTileHeight();
        }else{
            x+=tileSet->GetTileWidth();
        }
        contPos++;
    }
    
}

/*
    Renderiza as camadas do mapa.
*/
void TileMap::Render(){
    for(int layer = 0; layer < mapDepth; layer++){
        RenderLayer(layer, associeted.box.x,associeted.box.y);
    }
    
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
     if(strcmp(type.c_str(),"TileMap") == 0){
        return true;
    }
    return false;
}