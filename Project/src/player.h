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
            Vector2D endPos(x, y);

            engine->getKeyStatus(keys);

            if (keys.fire1){
                if (CanFire(0)){
                    Rocket * rocket = rockets_pool->FirstAvailable();
                    FireRocket(rocket, Vector2D(16, WINDOW_HEIGHT-52), endPos);
                }
            }


            if (keys.fire2){
                if (CanFire(1)){
                    Rocket * rocket = rockets_pool->FirstAvailable();
                    FireRocket(rocket, Vector2D(WINDOW_WIDTH/2 - 16, WINDOW_HEIGHT-52), endPos);
                }
            }

            if (keys.fire3){
                if (CanFire(2)){
                    Rocket * rocket = rockets_pool->FirstAvailable();
                    FireRocket(rocket, Vector2D(WINDOW_WIDTH-48, WINDOW_HEIGHT -52), endPos);
                }
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

    void FireRocket(Rocket * rocket, Vector2D startPos, Vector2D endPos){
        if (rocket != NULL){
            rocket->Init(startPos.x, endPos);
            Vector2D vel = endPos.operator-(startPos);
            vel.Normalize();
            rocket->GetComponent<RigidBodyComponent*>()->velocity = vel.operator*(ROCKET_SPEED);
            game_objects->insert(rocket);
        }
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
