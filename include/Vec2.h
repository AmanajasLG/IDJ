#pragma once 
#define INCLUDE_SDL
#include "../include/SDL_include.h"
#include <iostream>
#include <string>
using namespace std;

/*
Vec2 expressa um vetor no R2, que pode tanto representar uma posição no espaço como uma grandeza. 
*/
class Vec2 {
public:
    float x;
    float y;

    Vec2();

    Vec2(float x, float y);

    Vec2 AddVectors(Vec2 vector1, Vec2 vector2);
    
    Vec2 SubVectors(Vec2 vector1, Vec2 vector2);

    void MultScalar(Vec2 &vector, int scalar);

    float Magnitude(Vec2 vector);

    void NormalizeVec(Vec2 *vector);

    float Dist2Dots(Vec2 dot1, Vec2 dot2);

    void GetRotated(float angle);

    float VecInclination(Vec2 vector);
};