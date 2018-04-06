#include "../include/Game.h"
#include <iostream>
#include<string>
using namespace std;

int main (int argc, char** argv){
    Game *game = &Game::GetInstance();    

    game->Run();   
        
    return 0;
}