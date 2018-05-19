#include "../include/Game.h"
#include "../include/TitleState.h"
#include "../include/Resources.h"
#include <iostream>
#include<string>
using namespace std;

int main (int argc, char** argv){
    Game *game = &Game::GetInstance();   
    TitleState *titleState = new TitleState();
    game->Push(titleState);
    game->Run();   
        
    return 0;
}