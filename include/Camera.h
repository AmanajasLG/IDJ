#include "../include/GameObject.h"
#include "../include/Vec2.h"

class Camera{
private: 
    static GameObject *focus;

public:
    static Vec2 speed;
    static Vec2 pos;

    static void Follow(GameObject *newFocus);

    static void Unfollow();

    static void Update(float dt);
};

