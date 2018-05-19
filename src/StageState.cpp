#include "../include/StageState.h"
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
#include "../include/GameData.h"
#include "../include/Game.h"
#include "../include/EndState.h"
#include <math.h>

int dieCount = 0;

/* 
	O construtor de State inicializa quitRequested e instancia o Sprite.
*/ 
StageState::StageState() : State(){
    GameObject *background = new GameObject();
	Sprite *bg = new Sprite(*background);

	background->AddComponent(bg);
	objectArray.emplace_back(std::move(background));

	GameObject *gameTile = new GameObject();
	gameTile->box.x = 0;
	gameTile->box.y = 0;
	tileSet = new TileSet(64,64,"assets/img/tileset.png");
	
	TileMap *tilemap = new TileMap(*gameTile,"assets/map/tileMap.txt", tileSet);
	gameTile->AddComponent(tilemap);
	objectArray.emplace_back(std::move(gameTile));

	// Cria pinguins - T6 
	GameObject *penguinsGO = new GameObject();
	Sprite *spritePenguin = new Sprite(*penguinsGO,"assets/img/penguin.png");
    PenguinBody *pbody = new PenguinBody(*penguinsGO);

	penguinsGO->AddComponent(spritePenguin);
	pbody->player = pbody;
	penguinsGO->AddComponent(pbody);

	penguinsGO->box.w = spritePenguin->GetWidth();
	penguinsGO->box.h = spritePenguin->GetHeight();
	penguinsGO->box.x = 704 - penguinsGO->box.w/2;
	penguinsGO->box.y = 640 - penguinsGO->box.h/2;

	Camera::Follow(penguinsGO);

	objectArray.emplace_back(std::move(penguinsGO));
	
	// Cria alien - T4
	int numAlien = rand() % 4 + 1;

	for(int i = 0; i<numAlien; i++){
		int timeOffset = rand() % 5 + 1;
		
		GameObject *alienGO = new GameObject();
		Sprite *spriteAlien = new Sprite(*alienGO, "assets/img/alien.png");
		Alien *alien = new Alien(*alienGO, 6, timeOffset);

		alienGO->AddComponent(spriteAlien);
		alienGO->AddComponent(alien);

		alienGO->box.w = spriteAlien->GetWidth();
		alienGO->box.h = spriteAlien->GetHeight();
		alienGO->box.x = rand() % 600 * pow(-1,timeOffset)- alienGO->box.w/2 + penguinsGO->box.x ;
		alienGO->box.y = rand() % 600 * pow(-1,timeOffset) - alienGO->box.h/2 + penguinsGO->box.y ;

		objectArray.emplace_back(std::move(alienGO));
	}
}

StageState::~StageState(){
    
}

/*
O LoadAssets é uma método que cuida de pré-carregar os assets do state do jogo para que não haja problemas futuros como, por exemplo, o jogo tentar tocar a música antes dela terminar de ser carregada para a memória.
*/
void StageState::LoadAssets(){	
    Sprite *sprite = (Sprite*)objectArray[0]->GetComponent("Sprite");
	sprite->Open("assets/img/ocean.jpg");
    
    backgroundMusic.Open("assets/audio/stageState.ogg");
}

void StageState::Update(float dt){

    if(InputManager::GetInstance().KeyPressed(SDLK_ESCAPE)){
		popRequested = true;
	}

	
	Camera::Update(dt);

	int numAlien = 0;
	int numPenguin = 0;

	for(int i = 0;(size_t)i<objectArray.size();i++){
		objectArray[i]->Update(dt);

		if(objectArray[i]->GetComponent("Alien") != nullptr)
			numAlien++;

		if(objectArray[i]->GetComponent("PenguinBody") != nullptr)
			numPenguin++;
		

	}
	
	if((!numAlien || !numPenguin) && !dieCount){
		dieCount = 25;
	}
	
	if(dieCount){
		dieCount--;

		if(!dieCount){
			popRequested = true;

			if(!numAlien){
				EndState *endState = new EndState(true);
				Game::GetInstance().Push(endState);			
			}else{
				EndState *endState = new EndState(false);
				Game::GetInstance().Push(endState);
			}	
		}
	}

	for(int i = 0;(size_t)i<objectArray.size();i++){
		Collider *colliderA = (Collider*)objectArray[i]->GetComponent("Collider");
		if(colliderA != nullptr){
			for(int j = i+1;(size_t)j<objectArray.size();j++){
				Collider *colliderB = (Collider*)objectArray[j]->GetComponent("Collider");
				if(colliderB != nullptr){
					if(Collision::IsColliding(objectArray[i]->box,objectArray[j]->box,objectArray[i]->angleDeg,objectArray[j]->angleDeg)){
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}
	}

	for(int i = 0;(size_t)i<objectArray.size();i++){
		if(objectArray[i]->IsDead() && objectArray[i]->GetComponent("Minion") == nullptr){			
			Sound* sound = (Sound*)objectArray[i]->GetComponent("Sound");
			if(sound != nullptr){
				if(!sound->SoundIsPlaying())
					objectArray.erase(objectArray.begin() + i);
			}else{
				objectArray.erase(objectArray.begin() + i);
			}			
		}else if(objectArray[i]->IsDead()){
		
			objectArray.erase(objectArray.begin() + i);
		}
		
	}
}


void StageState::Render(){
    for(int i = 0;(size_t)i<objectArray.size();i++){
		if(i == 0){
			Sprite *sprite = (Sprite*)objectArray[i]->GetComponent("Sprite");
			sprite->Render(0,0);	
		}else{

			if(objectArray[i]->GetComponent("TileMap") != nullptr){
				objectArray[i]->box.x = Camera::pos.x;
				objectArray[i]->box.y = Camera::pos.y;
			}
			objectArray[i]->Render();
		}
	}
}


void StageState::Start(){
	LoadAssets();

	StartArray();
}

void StageState::Pause(){

}

void StageState::Resume(){

}