#pragma once 
#include "../include/GameObject.h"
#include <iostream>
#include <string>
using namespace std;

class GameObject;
/*
Essa é a classe que deve ser utilizada para adicionar lógica ao jogo utilizando herança.
Todos os componentes do nosso jogo terão, no mínimo, as seguintes características:
 - Referência ao GameObject que o contém.
 - Função que atualiza estado do componente.
 - Função para renderizar o que for necessário.
 - Função para se determinar o seu tipo.
*/
class Component {
protected:
    GameObject &associated; 

public:
    Component(GameObject &associated);

    virtual ~Component();

    void virtual Update(float dt) = 0;

    void virtual Render() = 0;

    bool virtual Is(std::string type)= 0;
};