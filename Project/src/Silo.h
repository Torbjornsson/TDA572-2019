#pragma once

class Silo : public GameObject{
    public:
        virtual void Init(double xPos){
            GameObject::Init();
            horizontalPos = xPos;
            verticalPos = WINDOW_HEIGHT - 32;
            radius = 16;
        }

        virtual void Receive(Message m){
            if (!enabled)
                return;

            if (m == HIT){
                SDL_Log("SILO::HIT");
                enabled = false;
            }
        }
};