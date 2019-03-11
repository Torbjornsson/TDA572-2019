#pragma once

class EnemyBehaviourComponent : public Component{
    ObjectPool<Missile> * missiles_pool;
    ObjectPool<GameObject> * towns;
    
    float time_pressed[3];
    int left_insilo[3];
    int x, y;

    public:
        virtual ~EnemyBehaviourComponent(){}

        virtual void Create(AvancezLib* engine, GameObject* go, std::set<GameObject*>* game_objects, ObjectPool<Missile>* missiles_pool, ObjectPool<GameObject>* towns){
            Component::Create(engine, go, game_objects);
            this->missiles_pool = missiles_pool;
            this->towns = towns;
        }

        virtual void Init(){
            x, y = 0;
            go->horizontalPos = x;
            go->verticalPos = y;

            for (int i = 0; i < 3; i++){
                time_pressed[i] = -10000.f;
                left_insilo[i] = 10;
            }
        }

        virtual void Update(float dt){
            go->horizontalPos = rand() % 640;
            Vector2D endPos = Vector2D(towns->SelectRandom()->horizontalPos+16, WINDOW_HEIGHT-32);
            if (CanFire(0)){    
                Missile * missile = missiles_pool->FirstAvailable();
                FireRocket(missile, Vector2D(go->horizontalPos, go->verticalPos), endPos);
            }
        }

    bool CanFire(int n){
		// shoot just if enough time passed by
        if (left_insilo[n] == 0){
            return false;
        }

		if ((engine->getElapsedTime() - time_pressed[n]) < (FIRE_TIME_INTERVAL / game_speed * 2))
			return false;

		time_pressed[n] = engine->getElapsedTime();
        left_insilo[n]--;

		SDL_Log("Missile! %i", n);
		return true;
	}

    void FireRocket(Missile * missile, Vector2D startPos, Vector2D endPos){
        if (missile != NULL){
            missile->Init(startPos.x, endPos);
            Vector2D vel = endPos.operator-(startPos);
            vel.Normalize();
            missile->GetComponent<RigidBodyComponent*>()->velocity = vel.operator*(ROCKET_SPEED);
            game_objects->insert(missile);
        }
    }

    void Reset(){
        left_insilo[0] = 10;
    }
};

class Enemy : public GameObject{

private:
    /* data */
public:
    virtual ~Enemy() {SDL_Log("Enemy::~Enemy");}

    virtual void Init(){
        SDL_Log("Enemy::Init");
        GameObject::Init();
    }

    virtual void Receive(Message m){
        if (m == HIT){
            SDL_Log("Enemy::HIT");            
        }
    }
};