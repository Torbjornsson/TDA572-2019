#pragma once

#include <vector>
#include "vector2D.h"

class Component;

enum Message { HIT, ALIEN_HIT, GAME_OVER, LEVEL_WIN, NO_MSG, QUIT };
class GameObject{
    protected:
        std::vector<GameObject*> receivers;
        std::vector<Component*> components;
        
    public:
        Vector2D start_pos;
        Vector2D end_pos;
        double horizontalPos;
        double verticalPos;
        double radius;

        bool enabled;

        virtual ~GameObject();

        virtual void Create();
        virtual void AddComponent(Component * component);

        virtual void Init();
        virtual void Update(float dt);
        virtual void Destroy();
        virtual void AddReceiver(GameObject * gameObject);
        virtual void Receive(Message m);
        void Send(Message m);
};