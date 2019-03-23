#include "Component.h"
#include "GameObject.h"
#include "avancezlib.h"

void RenderComponent::Create(AvancezLib* engine, GameObject* go, std::set<GameObject*> *game_objects, const char* sprite_name){
    Component::Create(engine, go, game_objects);

    this->sprite = engine->createSprite(sprite_name);
}

void RenderComponent::Update(float dt){
    if (!go->enabled){
        return;
    }
    if (sprite){
        sprite->draw(int(go->horizontalPos), int(go->verticalPos));
    }
}

void RenderComponent::Destroy(){
    if (sprite != NULL){
        sprite->destroy();
    }
    sprite = NULL;
}

Sprite* RenderComponent::GetSprite(){
    return sprite;
}