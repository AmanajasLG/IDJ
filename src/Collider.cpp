#include "../include/Collider.h"
#include "../include/Collision.h"
#include "../include/Camera.h"
#include "../include/Game.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated){
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt){
    box = associated.box;
    box.w *= scale.x;
    box.y *= scale.y;

    Vec2 center( box.Center(box) );

    Vec2 centerRotated = center.SubVectors(Vec2(box.x, box.y), center);
    centerRotated.GetRotated(associated.angleDeg/(180/M_PI));

    Vec2 centerPoint = center.AddVectors(center,centerRotated);
    centerPoint = center.SubVectors(centerPoint,Camera::pos);

}

bool Collider::Is(std::string type){
    return strcmp(type.c_str(),"Collider") == 0;
}

void Collider::SetScale(Vec2 scale){
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){
    this->offset = offset;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.Center(box) );
	SDL_Point points[5];

    Vec2 centerRotated = center.SubVectors(Vec2(box.x, box.y), center);
    centerRotated.GetRotated(associated.angleDeg/(180/M_PI));

    Vec2 centerPoint = center.AddVectors(center,centerRotated);
    centerPoint = center.SubVectors(centerPoint,Camera::pos);

	Vec2 point = center;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

    
    
    
    centerRotated = center.SubVectors(Vec2(box.x + box.w, box.y), center);
    centerRotated.GetRotated(associated.angleDeg/(180/M_PI));

    centerPoint = center.AddVectors(center,centerRotated);
    centerPoint = center.SubVectors(centerPoint,Camera::pos);
	
	point = centerPoint;
	points[1] = {(int)point.x, (int)point.y};

    
    
    
    centerRotated = center.SubVectors(Vec2(box.x + box.w, box.y + box.h), center);
    centerRotated.GetRotated(associated.angleDeg/(180/M_PI));

    centerPoint = center.AddVectors(center,centerRotated);
    centerPoint = center.SubVectors(centerPoint,Camera::pos);
	
	point = centerPoint;
	points[2] = {(int)point.x, (int)point.y};
    
    
    
    
    centerRotated = center.SubVectors(Vec2(box.x, box.y + box.h), center);
    centerRotated.GetRotated(associated.angleDeg/(180/M_PI));

    centerPoint = center.AddVectors(center,centerRotated);
    centerPoint = center.SubVectors(centerPoint,Camera::pos);
	
	point = centerPoint;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}