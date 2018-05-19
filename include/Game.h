#pragma once 
#include "../include/State.h"
#include <string>
#include <stack>
using namespace std;

/*
GAME é responsavel por inicializar recursos, rodar o loop principal do jogo e liberar os recursos quando o jogo for encerrado.
*/
class Game {
private:
    std::string title;
    int width;
    int height;
    SDL_Window *window;
    State *storedState;
    static Game *instance;
    SDL_Renderer *renderer;

    int frameStart;
    float dt;
    std::stack<std::unique_ptr<State>> stateStack;
    
    Game(string title, int width, int height);

    void CalculateDeltaTime();

public:
    ~Game();

    void Run();

    SDL_Renderer* GetRenderer();

    State& GetCurrentState();

    void Push(State *state);

    static Game& GetInstance();

    float GetDeltaTime();

    void PlayerWin();
};

