#include "Component.h"
#include "GameObject.h"
#include "avancezlib.h"

void CollideComponent::Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<GameObject>* coll_objects){
    Component::Create(engine, go, game_objects);

    this->coll_objects = coll_objects;
}

void CollideComponent::Update(float dt){
    for (auto i = 0; i < coll_objects->pool.size(); i++){
        GameObject * coll_go = coll_objects->pool[i];

        if (coll_go->enabled){
            if ((go->verticalPos - go->radius) <= coll_go->verticalPos){
                if (circleCollide(go, coll_go)){
                    go->Receive(HIT);
                    coll_go->Receive(HIT);            
                }
            }
        }
    }
}

//Check if 2 boxes overlap
bool CollideComponent::boxCollide(GameObject * go, GameObject * coll_go){
    return ((coll_go->horizontalPos > go->horizontalPos - 10) &&
        (coll_go->horizontalPos < go->horizontalPos + 10) &&
        (coll_go->verticalPos > go->verticalPos - 10) &&
        (coll_go->verticalPos < go->verticalPos + 10));
}

//Check if point is iside the circle
bool CollideComponent::circleCollide(GameObject * go, GameObject * coll_go){
    double x_diff = (go->horizontalPos + go->radius) - coll_go->horizontalPos;
    double y_diff = (go->verticalPos + go->radius) - coll_go->verticalPos;
    return (std::sqrt(x_diff * x_diff + y_diff * y_diff) <= go->radius);
}