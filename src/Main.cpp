#include "../include/Game.h"
#include "../include/Resources.h"
#include <iostream>
#include<string>
using namespace std;

int main (int argc, char** argv){
    Game *game = &Game::GetInstance();    
    
    game->Run();   

    Resources::ClearSounds();
    Resources::ClearMusics();
    Resources::ClearImages(); 
        
    return 0;
}