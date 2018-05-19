#include "../include/TitleState.h"
#include "../include/InputManager.h"
#include "../include/StageState.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/Text.h"

TitleState::TitleState() : State(){
    GameObject *title = new GameObject();
    title->box.x = 0;
    title->box.y = 0;
    Sprite *sprite = new Sprite(*title,"assets/img/title.jpg");
    title->box.w = sprite->GetWidth();
    title->box.h = sprite->GetHeight();


    title->AddComponent(sprite);
    objectArray.emplace_back(std::move(title));


    SDL_Color color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    GameObject *textGO = new GameObject();
    Text *text = new Text(*textGO,"assets/font/Call me maybe.ttf",60,Text::SOLID,"press space to continue!",color); 
    textGO->AddComponent(text);
    objectArray.emplace_back(std::move(textGO));
}

TitleState::~TitleState(){

}

void TitleState::Update(float dt){
    if(InputManager::GetInstance().KeyPressed(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}

    if(InputManager::GetInstance().KeyPressed(SDLK_SPACE)){
		StageState *stageState = new StageState();
        Game::GetInstance().Push(stageState);
	}

    for(int i = 0;(size_t)i<objectArray.size();i++){
		objectArray[i]->Update(dt);
	}
}

void TitleState::LoadAssets(){

}

void TitleState::Render(){
    RenderArray();
}

void TitleState::Start(){
    LoadAssets();

    StartArray();
}

void TitleState::Pause(){

}

void TitleState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;

    Render(); 
}
