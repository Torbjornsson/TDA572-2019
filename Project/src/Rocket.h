#pragma once

class RocketBehaviourComponent : public Component{
    ObjectPool<Explosion> *explosions_pool;
    public:
        virtual ~RocketBehaviourComponent(){}

        virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Explosion>* explosions_pool){
            Component::Create(engine, go, game_objects);
            this->explosions_pool = explosions_pool;
        }
        void Update(float dt){
            engine->drawLine(go->start_pos.x, go->start_pos.y, go->horizontalPos, go->verticalPos);

            //guard if missile goes out of the screen
            if (go->verticalPos < 0){
                go->enabled = false;
            }

            if (go->verticalPos < go->end_pos.y){
                SDL_Log("explode!!");
                Explosion * explosion = explosions_pool->FirstAvailable();
                if (explosion != NULL){
                    explosion->Init(go->horizontalPos, go->verticalPos, 4);
                    game_objects->insert(explosion);
                }
                go->enabled = false;
            }
        }
};

class Rocket : public GameObject{
    public:
        virtual void Init(double xPos, Vector2D endpos){
            SDL_Log("Rocket::Init");
            GameObject::Init();
            
            end_pos = endpos;
            double yPos = 480 - 32;
            
            horizontalPos = xPos;
            verticalPos = yPos;
            start_pos = Vector2D(xPos, yPos);
        }

        virtual void Receive(Message m){
            if (!enabled){
                return;
            }
        }
};