#pragma once

class Silo : public GameObject{
    public:
        virtual void Init(double xPos){
            GameObject::Init();
            horizontalPos = xPos;
            verticalPos = WINDOW_HEIGHT - 48;
        }

        virtual void Recieve(Message m){
            if (!enabled)
                return;

            if (m == HIT){
                enabled = false;
            }
        }
};