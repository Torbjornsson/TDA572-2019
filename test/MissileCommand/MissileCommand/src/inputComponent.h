#include "GameObject.h"

class inputComponent {
    public:
        virtual ~inputComponent(){}
        virtual void update(GameObject& obj) = 0;
};

class playerInputComponent : public inputComponent {
    private:

    public:
        virtual void update(GameObject& obj){

        }
};

class demoInputComponent : public inputComponent {
    private:

    public:
        virtual void update(GameObject& obj){

        }
};