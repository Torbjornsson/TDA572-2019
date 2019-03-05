#include "Component.h"
#include "avancezlib.h"
#include "GameObject.h"

void Component::Create(AvancezLib* engine, GameObject* go, std::set<GameObject*> * game_objects){
    this->engine = engine;
    this->go = go;
    this->game_objects = game_objects;
}

void RigidBodyComponent::Create(AvancezLib* engine, GameObject * go, std::set<GameObject*> * game_objects){
	Component::Create(engine, go, game_objects);
}

void RigidBodyComponent::Update(float dt){
	//Forward Euler method:
    Vector2D position(go->horizontalPos, go->verticalPos);
	position = position + velocity * dt;
    go->horizontalPos = position.x;
    go->verticalPos = position.y;
}