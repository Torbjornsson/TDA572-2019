#include <vector>

class Component;

enum Message { HIT, ALIEN_HIT, GAME_OVER, LEVEL_WIN, NO_MSG, QUIT };
class GameObject{
    protected:
        std::vector<GameObject*> receivers;
        std::vector<Component*> components;
        
    public:
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