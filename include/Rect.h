#pragma once 
#include "../include/Vec2.h"

/*
Rect expressa uma posição (canto superior esquerdo do retângulo) e dimensões.
*/
class Rect {
public:
    float x;
    float y;
    float w;
    float h;

    Rect();

    Rect(float x, float y, float w, float h);

    //Nas operações que tem apenas um rect sendo passado como parâmetro
    //o segundo parâmetro necessário será considerado o do proprio rect
    //que chama a função

    bool Contains(float mouseX,float mouseY);

    Vec2 Center(Rect rect);

    float Dist2Centers(Rect rect1, Rect rect2);

    void AddVec2Rect(Vec2 vector, Rect *rect);  
    

};