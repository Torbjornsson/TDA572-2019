#pragma once

class AlienBehaviourComponent : public Component {
    float time_fire;
    int direction = 1;
    ObjectPool<Bomb> * bomb_pool;
    double start_x, start_y;
    double distance = 0;

    public:
        virtual ~AlienBehaviourComponent(){}

        virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*> * game_objects, ObjectPool<Bomb> * bomb_pool){
            Component::Create(engine, go, game_objects);
            this->bomb_pool = bomb_pool;
        }
        
        virtual void Init(){                    
            direction = 1;
            distance = 0;
            time_fire = -10000.f;
        }

        virtual void Update(float dt){

            Move(dt * game_speed * ALIEN_SPEED * direction);
            distance += (dt * game_speed * ALIEN_SPEED);

            if (distance >= 640-32*8){
                distance = 0;
                direction *= -1;
                go->verticalPosition += 32;
            }

            if (go->verticalPosition >= 480)
                go->Send(GAME_OVER);
            
            if (rand() % 100000 < 10 && CanFire()){
                Bomb * bomb = bomb_pool->FirstAvailable();
                if (bomb != NULL) {
                    bomb->Init(go->horizontalPosition, go->verticalPosition);
                    game_objects->insert(bomb);
                }
                
            }
        }

        bool CanFire(){
		// shoot just if enough time passed by
		if ((engine->getElapsedTime() - time_fire) < (BOMB_TIME_INTERVAL / game_speed))
			return false;

		time_fire = engine->getElapsedTime();

		return true;
	}

        void Move(float move){
		    go->horizontalPosition += move;

		    if (go->horizontalPosition > (640 - 32)){
			    go->horizontalPosition = 640 - 32;
            }
			
		    if (go->horizontalPosition < 0)
			    go->horizontalPosition = 0;
	    }

        void Change_Dir(){
            direction *= -1;
        }

    private:
};

class Alien : public GameObject {
    public:
        bool change_direction = false;

        virtual ~Alien() {
            SDL_Log("Alien::~Alien");
        }

        virtual void Init(double x, double y){
            SDL_Log("Alien::init");
            horizontalPosition = x;
            verticalPosition = y;
            GameObject::Init();
        }

        virtual void Receive(Message m){
            if (!enabled)
                return;
                
            if (m == HIT) {
                SDL_Log("Alien::HIT");
                enabled = false;
                Send(ALIEN_HIT);
                Send(LEVEL_WIN);
            }
        }
};