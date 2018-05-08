#include "../include/Vec2.h"
#include <math.h>

Vec2::Vec2(){
    x = 0;
    y = 0;
}

Vec2::Vec2(float x, float y){
    this->x = x;
    this->y = y;
}

Vec2 Vec2::AddVectors(Vec2 vector1, Vec2 vector2){
    Vec2 vecsoma;

    vecsoma.x = vector1.x + vector2.x;
    vecsoma.y = vector1.y + vector2.y;

    return vecsoma;
}

Vec2 Vec2::SubVectors(Vec2 vector1, Vec2 vector2){
    Vec2 vecsub;

    vecsub.x = vector1.x - vector2.x;
    vecsub.y = vector1.y - vector2.y;

    return vecsub;
}

void Vec2::MultScalar(Vec2 &vector, int scalar){
    vector.x *= scalar;
    vector.y *= scalar;
}

float Vec2::Magnitude(Vec2 vector){
    return sqrt((float)pow(vector.x,2) + (float)pow(vector.y,2));
}

void Vec2::NormalizeVec(Vec2 *vector){
    float magnitude = Magnitude(*vector);

    vector->x /= magnitude; 
    vector->y /= magnitude;
}

float Vec2::Dist2Dots(Vec2 dot1, Vec2 dot2){
    return sqrt((float)pow((dot2.x - dot1.x),2) + (float)pow((dot2.y - dot1.y),2));
}

void Vec2::GetRotated(float angle){
    int x = this->x;
    int y = this->y;

    this->x = x * cos(angle) - y * sin(angle);   
    this->y = y * cos(angle) + x * sin(angle);    
}

float Vec2::VecInclination(Vec2 vector){
    return atan2(vector.y,vector.x);
}