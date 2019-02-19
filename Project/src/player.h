#pragma once

class PlayerBehaviourComponent : public Component{
    ObjectPool<Rocket> * rockets_pool;

    public:
        virtual ~PlayerBehaviourComponent(){}

        virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Rocket>* rockets_pool){
            Component::Create(engine, go, game_objects);
            this->rockets_pool = rockets_pool;
        }

        virtual void Init(){
            go->horizontalPosition = 0;
            go->verticalPosition = 0;
        }

        virtual void Update(float dt){
            AvancezLib::Keystatus keys;
            engine->getKeyStatus(keys);

            if (keys.fire1){
                SDL_Log("fire1");
            }

            if (keys.fire2){
                SDL_Log("fire2");
            }

            if (keys.fire3){
                SDL_Log("fire3");
            }
        }
}