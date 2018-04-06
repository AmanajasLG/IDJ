#include "../include/Rect.h"

Rect::Rect(){
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

bool Rect::Contains(float mouseX,float mouseY){
    int xMax = this->x + this->w;
    int xMin = this->x;
    int yMax = this->y + this->h;
    int yMin = this->y;

    if((mouseX <= xMax && mouseX >= xMin) && (mouseY <= yMax && mouseY >= yMin))
        return true;
    
    return false;
}

Vec2 Rect::Center(Rect rect){
    int meioX = rect.w/2;
    int meioY = rect.h/2;

    meioX += rect.x;
    meioY += rect.y;

    return Vec2(meioX, meioY);
}

float Rect::Dist2Centers(Rect rect1, Rect rect2){
    Vec2 center1 = Center(rect1);
    Vec2 center2 = Center(rect2);

    return center1.Dist2Dots(center1,center2);
}

void AddVec2Rect(Vec2 vector, Rect *rect){
    rect->x += vector.x;
    rect->y += vector.y;
}