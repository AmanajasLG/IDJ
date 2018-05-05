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
#include <math.h>

/* 
	O construtor de State inicializa quitRequested e instancia o Sprite.
*/ 
State::State(){
    quitRequested = false;
	started = false;

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

	// Cria alien - T4
	GameObject *alienGO = new GameObject();
	Sprite *sprite = new Sprite(*alienGO, "assets/img/alien.png");
	Alien *alien = new Alien(*alienGO, 2);

	alienGO->AddComponent(sprite);
	alienGO->AddComponent(alien);

	alienGO->box.w = sprite->GetWidth();
	alienGO->box.h = sprite->GetHeight();
	alienGO->box.x = 512 - alienGO->box.w/2 + Camera::pos.x;
	alienGO->box.y = 300 - alienGO->box.h/2 + Camera::pos.y;

	objectArray.emplace_back(std::move(alienGO));
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

				if(go->box.Contains(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y) ) {
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
			if(objectArray[i]->GetComponent("Bullet") != nullptr)
				objectArray.erase(objectArray.begin() + i);
				continue;
			
			Sound* sound = (Sound*)objectArray[i]->GetComponent("Sound");
			if(!sound->SoundIsPlaying()){
				objectArray.erase(objectArray.begin() + i);
			}			
		}
		
	}
}


void State::Render(){
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

void State::AddObject(int mouseX, int mouseY){
	GameObject *enemy = new GameObject();
	Sprite *sprite = new Sprite(*enemy, "assets/img/penguinface.png");
	Sound *sound = new Sound(*enemy, "assets/audio/boom.wav");
	Face *face = new Face(*enemy);

	enemy->AddComponent(face);
	enemy->AddComponent(sprite);

	enemy->box.w = sprite->GetWidth();
	enemy->box.h = sprite->GetHeight();

	enemy->box.x = mouseX - enemy->box.w/2 - Camera::pos.x;
	enemy->box.y = mouseY - enemy->box.h/2 - Camera::pos.y;

	
	enemy->AddComponent(sound);
	
	objectArray.emplace_back(std::move(enemy));	
	
}


void State::Start(){
	LoadAssets();

	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Start();
	}

	started = true;
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