#pragma once

class PlayerBehaviourComponent : public Component{
    ObjectPool<Rocket> * rockets_pool;
    float time_pressed[3];
    int x, y;

    public:
        virtual ~PlayerBehaviourComponent(){}

        virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Rocket>* rockets_pool){
            Component::Create(engine, go, game_objects);
            this->rockets_pool = rockets_pool;
        }

        virtual void Init(){
            x, y = 0;
            go->horizontalPos = x;
            go->verticalPos = y;

            for (int i = 0; i < 3; i++){
                time_pressed[i] = -10000.f;
            }
        }

        virtual void Update(float dt){
            AvancezLib::KeyStatus keys;
            
            SDL_GetMouseState(&x, &y);
            go->horizontalPos = x-16;
            go->verticalPos = y-16;

            engine->getKeyStatus(keys);

            if (keys.fire1){
                if (CanFire(0)){
                    Rocket * rocket = rockets_pool->FirstAvailable();
                    if (rocket != NULL){
                        rocket->Init(go->horizontalPos);
                        game_objects->insert(rocket);
                    }

                   engine->drawCircle(go->horizontalPos, go->verticalPos, 30);
                }
            }


            if (keys.fire2){
                CanFire(1);
            }

            if (keys.fire3){
                CanFire(2);
            }
        }

        bool CanFire(int n)
	    {
		// shoot just if enough time passed by
		if ((engine->getElapsedTime() - time_pressed[n]) < (FIRE_TIME_INTERVAL / game_speed))
			return false;

		time_pressed[n] = engine->getElapsedTime();

		SDL_Log("fire! %i", n);
		return true;
	}
};

class Player : public GameObject{

private:
    /* data */
public:
    virtual ~Player() {SDL_Log("Player::~Player");}

    virtual void Init(){
        SDL_Log("Player::Init");
        GameObject::Init();
    }

    virtual void Receive(Message m){
        if (m == HIT){
            SDL_Log("Player::HIT");

            
        }
    }
};
