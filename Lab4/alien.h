#pragma once

class AlienBehaviourComponent : public Component {
    float time_fire;
    int direction = 1;
    ObjectPool<Bomb> * bomb_pool;
    
    public:
        virtual ~AlienBehaviourComponent(){}

        virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*> * game_objects, ObjectPool<Bomb> * bomb_pool){
            Component::Create(engine, go, game_objects);
            this->bomb_pool = bomb_pool;
        }
        
        virtual void Init(){
            go->horizontalPosition = 100;
            go->verticalPosition = 100;

            time_fire = -10000.f;
        }

        virtual void Update(float dt){
            if (go->horizontalPosition >= 640-32 && direction == 1){
                direction = -1;
                go->verticalPosition += 32;
            }
                
            if (go->horizontalPosition <= 0 && direction == -1){
                direction = 1;
                go->verticalPosition += 32;
            }

            Move(dt * game_speed * ALIEN_SPEED * direction);

            if (rand() % 10000 < 10){
                Bomb * bomb = bomb_pool->FirstAvailable();
                if (bomb != NULL) {
                    bomb->Init(go->horizontalPosition, go->verticalPosition);
                    game_objects->insert(bomb);
                }
                
            }
        }

        void Move(float move){
		    go->horizontalPosition += move;

		    if (go->horizontalPosition > (640 - 32))
			    go->horizontalPosition = 640 - 32;
			
		    if (go->horizontalPosition < 0)
			    go->horizontalPosition = 0;
	    }

    private:
};

class Alien : public GameObject {
    public:

        virtual ~Alien() {
            SDL_Log("Alien::~Alien");
        }

        virtual void Init(){
            SDL_Log("Alien::init");
            GameObject::Init();
        }

        virtual void Recieve(Message m){
            if (!enabled)
                return;
                
            if (m == HIT) {
                SDL_Log("Alien::HIT");
                enabled = false;
                Send(ALIEN_HIT);
            }
        }
};