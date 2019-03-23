#pragma once

class MissileBehaviourComponent : public Component{
    public:
        void Update(float dt){
            engine->drawLine(go->start_pos.x, go->start_pos.y, go->horizontalPos, go->verticalPos);

            if (go->verticalPos >= WINDOW_HEIGHT){
                go->Send(LEVEL_WIN);
                go->enabled = false;
            }
        }
};

class Missile : public GameObject{
    public:
        virtual void Init(double xPos, Vector2D endpos){
            SDL_Log("Missile::Init");
            GameObject::Init();
            start_pos = Vector2D(xPos, 0);
            end_pos = endpos;
            horizontalPos = xPos;
            verticalPos = 0;
            radius = 1;
        }

        virtual void Receive(Message m){
            if (!enabled){
                return;
            }

            if (m == HIT){
                enabled = false;
                SDL_Log("Missile::Hit");
                Send(LEVEL_WIN);
                Send(GAME_OVER);
            }
        }
};