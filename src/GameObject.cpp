#include "../include/GameObject.h"


GameObject::GameObject(){
    isDead = false;
}

/*
Percorre vetor de components dando delete em todos e depois dando
clear no vetor. Dica: Percorra o vetor de trás para frente e chame delete
usando o iterador do começo mais o index atual.
*/
GameObject::~GameObject(){

    for(int i = components.size();i>0;i--){
        components.erase(components.begin() + (i-1));
    }
    
    components.clear();
}

/*
Percorre o vetor de componentes chamando o Update(dt) dos
mesmos.
*/
void GameObject::Update(float dt){

    for(int i = 0;(size_t)i<components.size();i++){
        components[i]->Update(dt);
    }
}

/*
Percorre o vetor de componentes chamando o Render dos mesmos.
*/
void GameObject::Render(){

    for(int i = 0;(size_t)i<components.size();i++){
        components[i]->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

/*
Adiciona o componente ao vetor de componentes.
*/
void GameObject::AddComponent(Component *cpt){   
    components.emplace_back(std::move(cpt));
}

/*
Remove o componente do vetor de componentes.
*/
void GameObject::RemoveComponent(Component *cpt){
    if (cpt == nullptr) return;
    for(int i = components.size();i>=0;i--){
        if(components[i].get() == cpt){
            components.erase(components.begin() + i);
            
            return;
        }
    }
}

/*
Retorna um ponteiro para o componente do tipo solicitado que estiver
adicionado nesse objeto. nullptr caso esse componente não exista.
*/
Component *GameObject::GetComponent(std::string type){
    if(components.empty()){
        return nullptr;
    }

    for(int i = 0;i<components.size();i++){
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }

    return nullptr;
}