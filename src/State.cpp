#include "../include/State.h"
#include "../include/Vec2.h"
#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Rect.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Alien.h"
#include "../include/PenguinBody.h"
#include "../include/Collider.h"
#include "../include/Collision.h"
#include <math.h>

/* 
	O construtor de State inicializa quitRequested e instancia o Sprite.
*/ 
State::State(){
    quitRequested = false;
	started = false;
	popRequested = false;
}

State::~State(){
    objectArray.clear();
}

/*
As condições de saída do programa são o usuário clicar no “X” da janela ou apertar Alt+F4.
*/

/*
QuitRequested retorna o valor da flag de mesmo nome na função, que será usado por Game para interromper o game loop.
*/
bool State::QuitRequested(){
    return quitRequested;
}

bool State::PopRequested(){
    return popRequested;
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go){
	std::shared_ptr<GameObject> sharedGO(go);

	objectArray.push_back(sharedGO);

	if(started == true){
		objectArray[objectArray.size() - 1]->Start();
	}

	std::weak_ptr<GameObject> weakGO(sharedGO);

	return weakGO;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go){
	for(int i = 0; i < objectArray.size(); i++){
		if(objectArray[i].get() == go){
			std::weak_ptr<GameObject> weakGO(objectArray[i]);
			return weakGO;
		}
	}

	std::weak_ptr<GameObject> weakGO;
	return weakGO;
	
}

void State::StartArray(){

	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Start();
	}

	started = true;
}

void State::UpdateArray(float dt){
	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Update(dt);
	}
}

void State::RenderArray(){

	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Render();
	}
}

