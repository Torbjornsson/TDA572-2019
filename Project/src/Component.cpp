#include "Component.h"

Component::Create(AvancezLib* engine, GameObject* go, std::set<GameObject*> * game_objects){
    this->engine = engine;
    this->go = go;
    this->game_objects = game_objects;
}

Component::Init(){

}
