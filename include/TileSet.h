#pragma once
#include "../include/Sprite.h"
#include <iostream>
#include <string>
using namespace std;

/*
    Uma classe de tileset é responsável por armazenar os tiles utilizados na
    renderização do TileMap. Internamente, os tiles fazem parte de um grande
    Sprite. Quando queremos renderizar um deles, recortamos usando o clip do Sprite.
*/
class TileSet{
private:
    Sprite *tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;

public:
    TileSet(int tileWidth, int tileHeight, std::string file);

    void RenderTile(unsigned index, float x, float y);

    int GetTileWidth();

    int GetTileHeight();
};