#include "../include/State.h"
#include "../include/Vec2.h"
#include "../include/Face.h"
#include "../include/Sound.h"
#include "../include/Rect.h"
#include <math.h>


/* 
O construtor de State inicializa quitRequested e instancia o Sprite.
*/ 
State::State(){
    quitRequested = false;
    GameObject *background = new GameObject();
	Sound *sound = new Sound(*background);
	bg = new Sprite(*background);

	background->AddComponent(bg);
	background->AddComponent(sound);
	
	objectArray.emplace_back(std::move(background));	
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
    music.Open("assets/audio/stageState.ogg");
    bg->Open("assets/img/ocean.jpg");	
}

void State::Update(float dt){
    Input();

	for(int i = 0;(size_t)i<objectArray.size();i++){
		objectArray[i]->Update(dt);
	}

	for(int i = 0;(size_t)i<objectArray.size();i++){
		if(objectArray[i]->IsDead()){
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::Render(){
    for(int i = 0;(size_t)i<objectArray.size();i++){
		objectArray[i]->Render();
	}
}

void State::Input(){

    SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( (float)mouseX, (float)mouseY ) ) {  
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
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 vec = Vec2(200, 0);
				vec.GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 );
				Vec2 objPos = objPos.AddVectors(vec, Vec2( mouseX, mouseY ));
				AddObject((int)objPos.x, (int)objPos.y);

			}
		}
	}
    
}

void State::AddObject(int mouseX, int mouseY){
	GameObject *enemy = new GameObject();
	Sprite *sprite = new Sprite(*enemy, "assets/img/penguinface.png");
	Sound *sound = new Sound(*enemy, "assets/audio/boom.wav");
	Face *face = new Face(*enemy);

	enemy->AddComponent(sprite);

	enemy->box.w = sprite->GetWidth();
	enemy->box.h = sprite->GetHeight();

	enemy->box.x = mouseX + enemy->box.w/2;
	enemy->box.y = mouseY + enemy->box.h/2;

	
	enemy->AddComponent(sound);
	enemy->AddComponent(face);
	
	objectArray.emplace_back(std::move(enemy));	
	
}