#pragma once

class RocketBehaviourComponent : public Component{
    public:
        void Update(float dt){
            //make a travel speed for player missiles
            go->verticalPos -= 10 * dt;

            //guard if missile goes out of the screen
            if (go->verticalPos < 0){
                go->enabled = false;
            }
        }
};

class Rocket : public GameObject{
    public:
        virtual void Init(double xPos){
            SDL_Log("Rocket::Init");
            GameObject::Init();

            horizontalPos = xPos;
            verticalPos = 480 - 52;
        }

        virtual void Receive(Message m){
            if (!enabled){
                return;
            }

            if (m == HIT){
                //change to a timer and expand radious
                enabled = false;
                SDL_Log("Rocket::Hit");
            }
        }
};