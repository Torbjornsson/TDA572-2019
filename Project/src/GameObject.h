#include <vector>

class Component;

class GameObject{
    protected:
        std::vector<GameObject*> recievers;
        std::vector<Component*> components;
        
    public:
        double horizontalPos;
        double verticalPos;

        bool enabled;

        ~virtual GameObject();

        virtual void Create();
        virtual void AddComponent(Component * component);

        virtual void Init();
        virtual void Update(float dt);
        virtual void Destroy();
        virtual void AddReceiver(GameObject * gameObject);
        virtual void Receive(Message m){}
        void Send(Message m);
};