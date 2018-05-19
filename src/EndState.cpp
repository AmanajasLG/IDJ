#include "../include/EndState.h"
#include "../include/GameData.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Text.h"

EndState::EndState(bool playerVictory){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    
    if(playerVictory){
        GameObject *go = new GameObject();
        Sprite *bg = new Sprite(*go,"assets/img/win.jpg");
        go->box.x= 0;
        go->box.y= 0;
        go->AddComponent(bg);

        objectArray.emplace_back(std::move(go));

        backgroundMusic.Open("assets/audio/endStateWin.ogg");
    }else{

        GameObject *go = new GameObject();
        Sprite *bg = new Sprite(*go,"assets/img/lose.jpg");
        go->box.x= 0;
        go->box.y= 0;
        go->AddComponent(bg);

        objectArray.emplace_back(std::move(go));

        backgroundMusic.Open("assets/audio/endStateLose.ogg");
    }

    SDL_Color color;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    GameObject *textGO = new GameObject();
    Text *text = new Text(*textGO,"assets/font/Call me maybe.ttf",60,Text::SOLID,"press space to continue!",color); 
    textGO->AddComponent(text);
    objectArray.emplace_back(std::move(textGO));
}

EndState::~EndState(){

}

void EndState::Update(float dt){
    if(InputManager::GetInstance().KeyPressed(SDLK_ESCAPE)){
		quitRequested = true;
	}

    if(InputManager::GetInstance().KeyPressed(SDLK_SPACE)){
        popRequested = true;
    }

    for(int i = 0;(size_t)i<objectArray.size();i++){
		objectArray[i]->Update(dt);
	}
}

void EndState::LoadAssets(){

}

void EndState::Render(){
    RenderArray();
}

void EndState::Start(){
	LoadAssets();

	StartArray();
}

void EndState::Pause(){

}

void EndState::Resume(){

}
