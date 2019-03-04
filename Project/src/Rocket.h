#pragma once

class RocketBehaviourComponent : public Component{
    public:
        void Update(float dt){
            //make a travel speed for player missiles
            //go->verticalPos -= ROCKET_SPEED * dt;

            float d = go->start_pos.dotProduct(go->end_pos);
            Vector2D a = go->start_pos+Vector2D(ROCKET_SPEED * dt * d, ROCKET_SPEED * dt * d);
            go->horizontalPos = a.x;
            go->verticalPos = a.y;

            //guard if missile goes out of the screen
            if (go->verticalPos < 0){
                go->enabled = false;
            }

            if (go->verticalPos <= go->end_pos.y && go->horizontalPos == go->end_pos.x){
                SDL_Log("explode!!");
            }
        }
};

class Rocket : public GameObject{
    public:
        virtual void Init(double xPos, Vector2D endpos){
            SDL_Log("Rocket::Init");
            GameObject::Init();
            
            end_pos = endpos;
            double yPos = 480 - 52;
            
            horizontalPos = xPos;
            verticalPos = yPos;
            start_pos = Vector2D(xPos, yPos);
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