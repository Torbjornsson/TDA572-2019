#pragma once

class ExplosionBehaviourComponent : public Component{
    public:
        void Update(float dt){
            go->radius = go->radius + dt * 16;
            engine->drawCircle(go->horizontalPos, go->verticalPos, go->radius);

            if (go->radius >= 32){
                go->enabled = false;
            }
        }
};

class Explosion : public GameObject{
    public:
        virtual void Init(double xPos, double yPos, double rad){
            GameObject::Init();

            horizontalPos = xPos;
            verticalPos = yPos;
            radius = rad;
        }

        virtual void Receive(Message m){
            if (!enabled){
                return;
            }
            if (m == HIT)
                Send(MISSILE_HIT);
        }
};