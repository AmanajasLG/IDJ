#include "../include/State.h"
#include "../include/Vec2.h"
#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Rect.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include <math.h>

/* 
	O construtor de State inicializa quitRequested e instancia o Sprite.
*/ 
State::State(){
    quitRequested = false;

	// Mudança T2
    GameObject *background = new GameObject();
	bg = new Sprite(*background);

	background->AddComponent(bg);
	
	objectArray.emplace_back(std::move(background));

	// Mudança T3
	GameObject *gameTile = new GameObject();
	gameTile->box.x = 0;
	gameTile->box.y = 0;
	TileSet *tileset = new TileSet(64,64,"assets/img/tileset.png");
	
	TileMap *tilemap = new TileMap(*gameTile,"assets/map/tileMap.txt", tileset);
	gameTile->AddComponent(tilemap);
	objectArray.emplace_back(std::move(gameTile));
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

/*
O LoadAssets é uma método que cuida de pré-carregar os assets do state do jogo para que não haja problemas futuros como, por exemplo, o jogo tentar tocar a música antes dela terminar de ser carregada para a memória.
*/
void State::LoadAssets(){
	bg->Open("assets/img/ocean.jpg");	
    music.Open("assets/audio/stageState.ogg");
}

void State::Update(float dt){
	for(int i = 0;i<6;i++){
		if(InputManager::GetInstance().MousePressed(i)) {
			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
	}

    if(InputManager::GetInstance().KeyPressed(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

	if(InputManager::GetInstance().KeyPressed(SDLK_SPACE)){
		Vec2 vec = Vec2(200, 0);
		vec.GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 );
		Vec2 objPos = objPos.AddVectors(vec, Vec2( InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY()));
		AddObject((int)objPos.x, (int)objPos.y);
	}

	
	Camera::Update(dt);

	for(int i = 0;(size_t)i<objectArray.size();i++){
		objectArray[i]->Update(dt);
	}

	for(int i = 0;(size_t)i<objectArray.size();i++){
		if(objectArray[i]->IsDead()){
			Sound* sound = (Sound*)objectArray[i]->GetComponent("Sound");
			if(!sound->SoundIsPlaying()){
				objectArray.erase(objectArray.begin() + i);
			}			
		}
		
	}
}


void State::Render(){
    for(int i = 0;(size_t)i<objectArray.size();i++){
		if(objectArray[i]->GetComponent("TileMap") != nullptr){
			objectArray[i]->box.x = Camera::pos.x;
			objectArray[i]->box.y = Camera::pos.y;
		}
		objectArray[i]->Render();
	}
}

void State::AddObject(int mouseX, int mouseY){
	GameObject *enemy = new GameObject();
	Sprite *sprite = new Sprite(*enemy, "assets/img/penguinface.png");
	Sound *sound = new Sound(*enemy, "assets/audio/boom.wav");
	Face *face = new Face(*enemy);

	enemy->AddComponent(face);
	enemy->AddComponent(sprite);

	enemy->box.w = sprite->GetWidth();
	enemy->box.h = sprite->GetHeight();

	enemy->box.x = mouseX;
	enemy->box.y = mouseY;

	
	enemy->AddComponent(sound);
	
	objectArray.emplace_back(std::move(enemy));	
	
}