#pragma once

class PlayerBehaviourComponent : public Component{
    ObjectPool<Rocket> * rockets_pool;
    float time_fire_pressed;

    public:
        virtual ~PlayerBehaviourComponent(){}

        virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Rocket>* rockets_pool){
            Component::Create(engine, go, game_objects);
            this->rockets_pool = rockets_pool;
        }

        virtual void Init(){
            go->horizontalPos = 0;
            go->verticalPos = 0;

            time_fire_pressed = -1000000.f;
        }

        virtual void Update(float dt){
            AvancezLib::KeyStatus keys;
            engine->getKeyStatus(keys);

            if (keys.fire1){
                if (CanFire())
                    SDL_Log("1");
            }

            if (keys.fire2){
                CanFire();
            }

            if (keys.fire3){
                CanFire();
            }
        }

        bool CanFire()
	    {
		// shoot just if enough time passed by
		if ((engine->getElapsedTime() - time_fire_pressed) < (FIRE_TIME_INTERVAL / game_speed))
			return false;

		time_fire_pressed = engine->getElapsedTime();

		SDL_Log("fire!");
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
