#pragma once

class MissileBehaviourComponent : public Component{
    public:
        void Update(float dt){

            engine->drawLine(go->start_pos.x, go->start_pos.y, go->horizontalPos, go->verticalPos);
            SDL_Log("test");

            if (go->verticalPos >= WINDOW_HEIGHT)
                go->enabled = false;
        }
};

class Missile : public GameObject{
    public:
        virtual void Init(double xPos, Vector2D endpos){
            SDL_Log("Missile::Init");
            GameObject::Init();
            start_pos = Vector2D(xPos, 0);
            end_pos = endpos;
            horizontalPos = 0;
            verticalPos = 0;
        }

        virtual void Receive(Message m){
            if (!enabled){
                return;
            }

            if (m == HIT){
                //change to a timer and expand radious
                enabled = false;
                SDL_Log("Missile::Hit");
            }
        }
};