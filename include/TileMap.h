#pragma once 
#define INCLUDE_SDL_IMAGE
#include "../include/SDL_include.h"
#include "../include/Component.h"
#include "../include/TileSet.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
    Simula uma matriz tridimensional, representando nosso mapa e suas 
    diversas camadas. Essa matriz contém, em cada posição, um índice de
    tile no TileSet.
*/
class TileMap : public Component{
private:
    std::vector<int> tileMatrix;
    TileSet *tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;

public:
    TileMap(GameObject &associetated, std::string file, TileSet *tileSet);

    void Load(std::string file);

    void SetTileSet(TileSet *tileSet);

    int &At(int x, int y, int z = 0);

    void Render();

    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth();

    int GetHeight();

    int GetDepth();

    void Update(float dt);

    bool Is(std::string type);
};