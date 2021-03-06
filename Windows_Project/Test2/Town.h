#pragma once

class TownBehaviourComponent : public Component{
    public:
        void Update(float dt){

        }
};

class Town : public GameObject{
    public:
        virtual void Init(double xPos){
            SDL_Log("Init");
            GameObject::Init();
            horizontalPos = xPos;
            verticalPos = WINDOW_HEIGHT - 48;
            radius = 16;
        }

        virtual void Receive(Message m){
            if (!enabled)
                return;

            if (m == HIT){
                enabled = false;
                SDL_Log("Town:HIT");
            }
        }
};