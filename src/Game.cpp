#include "../include/Game.h"
#include "../include/InputManager.h"
#include<cstdlib>
#include<ctime>

Game *Game::instance = nullptr;


/*
    Quando a classe é instanciada, a primeira coisa a se fazer é checar se já há uma instância dela rodando (instance != nullptr). Se já existir, há um problema na lógica do seu jogo. Se não existir, atribua this a instance.
*/
Game::Game(string title, int width, int height){
    if(instance != nullptr){
        cout<< "Erro encontrado! Instância já existe!" <<endl;
        return;
    }

    instance = this;
   
    /*
    A SDL_Init retorna diferente de zero quando falha. Caso isso aconteça, deve-se abortar o programa com uma mensagem de erro. Convém usar SDL_GetError para saber a causa.
    */        
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        cout<< "ERRO: " << SDL_GetError() <<endl;
        return;
    }

    /*
    Criando janela e um renderizador. Testa falha com nullptr.
    */
    window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(window == nullptr || renderer == nullptr){
        cout<< "Falha ao criar janela!" <<endl;
        cout<< "ERRO: " << SDL_GetError() <<endl;
        return;
    }

    /*
    Iniciando biblioteca de imagens e sons
    */
    if(IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG){
        cout<< "Falha ao iniciar SDL_image!\n";
        return;
    }
    if(Mix_Init(MIX_INIT_OGG) < 0){
        cout<< "Falha ao iniciar SDL_mixer!\n";
        return; 
    }
    Mix_SetSoundFonts("assets");
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) != 0){
        cout<< "Falha ao iniciar OpenAudio()!\n";
        return;
    }
    Mix_AllocateChannels(32);    

    srand(time(NULL));

    frameStart = SDL_GetTicks();
    dt = 0;
}


/*
    O destrutor desfaz as inicializações: deleta o estado, encerra a SDL_Music(Mix_CloseAudio e Mix_Quit) e a SDL_image (IMG_Quit), destrói o renderizador e a janela (SDL_DestroyRenderer, SDL_DestroyWindow), e, finalmente, encerra a SDL (SDL_Quit).
*/
Game::~Game(){
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*
    Run é um simples loop, que funciona enquanto QuitRequested não retornar true. Dentro desse loop, chamamos Update e Render do estado. Em seguida, chamamos a função SDL_RenderPresent, que força o renderizador passado como argumento a atualizar a tela com as últimas renderizações feitas. Sem chamar essa função,a janela continuará vazia.
*/
void Game::Run(){
    state->Start();
    
    while(!state->QuitRequested()){
        InputManager::GetInstance().Update();
        CalculateDeltaTime();
        state->Update(GetDeltaTime());
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(33);
    }
}

/*
    Retorna renderer
*/
SDL_Renderer* Game::GetRenderer(){
    return renderer;    
}

/*
    Retorna state
*/
State& Game::GetState(){
    if(state == nullptr){
        state = new State();
    }
    return *state;
}

/*
    Nesse método, a primeira coisa a se fazer é checar se já há uma instância dela rodando (instance != nullptr), se já existir, o retorne. Se não existir, instancie a primeira (e única!) instância de Game usando new.
*/
Game& Game::GetInstance(){
    
    if(instance != nullptr){
        return *instance;
    }
    instance = new Game("Luiza_Amanajas_160056659",1024,600); 
    instance->state = &instance->GetState();
    
    return *instance;
}

/*
    Atribui valor a dt, e deve ser chamada no início de
    cada iteração do main game loop.
*/
void Game::CalculateDeltaTime(){
    int frameEnd = SDL_GetTicks();
    dt = floor((frameEnd - frameStart)/10);
    frameStart = frameEnd;
}

float Game::GetDeltaTime(){
    return dt;
}