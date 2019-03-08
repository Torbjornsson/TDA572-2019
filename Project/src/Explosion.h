#pragma once

class ExplosionBehaviourComponent : public Component{
    public:
        void Update(float dt){
            go->radius = go->radius + dt * 4;
            engine->drawCircle(go->horizontalPos, go->verticalPos, go->radius);

            if (go->radius >= 32){
                SDL_Log("Explosion::fin");
                go->enabled = false;
            }
        }
};

class Explosion : public GameObject{
    public:
        virtual void Init(double xPos, double yPos, double radius){
            SDL_Log("Explosion::Init");
            GameObject::Init();

            horizontalPos = xPos;
            verticalPos = yPos;
            radius = radius;

        }

        virtual void Receive(Message m){
            if (!enabled){
                return;
            }

            if (m == HIT){
                //change to a timer and expand radious
                //enabled = false;
                SDL_Log("Explosion::Hit");
            }
        }
};