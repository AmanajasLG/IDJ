#include "../include/Music.h"
#include "../include/Resources.h"

/*
O segundo construtor chama Open, o primeiro apenas inicializa music como nullptr, para aguardar uma chamada a Open vinda de fora da função.
*/
Music::Music(){
    music = nullptr;
}

Music::Music(std::string file){
    music = nullptr;
    Open(file);
    Play();
}

Music::~Music(){
    Stop(); 
}

/*
Mix_PlayMusic recebe uma música e quantas vezes ela deve ser tocada. Se loops for -1, a música repete infinitamente. Se loops for 0, a música não é tocada. Vale notar que a Mixer só suporta uma música sendo tocada por vez: Se outra música já estiver tocando, ela para.
*/
void Music::Play(int times){
    if(music == nullptr){
        std::cout<< "Erro ao tocar musica! Não há musica iniciada!" <<endl;
        return;
    }

    Mix_PlayMusic(music,times);
}

/*
Mix_FadeOutMusic para a música atual dando um efeito de fade, isto é, diminuindo gradualmente o volume até chegar em 0. O tempo para a música parar totalmente é passado como argumento da função, em milissegundos. Vamos deixar default como 1,5 segundos. Caso queria que pare imediatamente, basta passar 0 como argumento.
*/
void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}

/*
Carrega a música indicada no arquivo file.
*/
void Music::Open(std::string file){
    music = Resources::GetMusic(file);
    
    Play(-1);
}

bool Music::IsOpen(){
    if(music == nullptr){
        return false;
    }
    return true;
}
