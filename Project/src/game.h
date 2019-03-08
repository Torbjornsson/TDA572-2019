    #pragma once

class Game : public GameObject{
    //the set of all game objects in the game
    std::set<GameObject*> game_objects;

    AvancezLib* engine;

    bool game_over, level_win;

    int missiles = 10;

    unsigned int score = 0;

    Sprite * missile_sprite;

    Player * player;

    Enemy * enemy;
    
    ObjectPool<Rocket> rockets_pool;

    ObjectPool<Explosion> explosions_pool;

    ObjectPool<Missile> missiles_pool;

    ObjectPool<Town> town_pool;

    ObjectPool<Silo> silo_pool;

   public:
    virtual void Create(AvancezLib* engine){
        //MOVE THIS!!!
        SDL_Log("Game::Create");

        this->engine = engine;

        player = new Player();
        PlayerBehaviourComponent * player_behaviour = new PlayerBehaviourComponent();
        player_behaviour->Create(engine, player, &game_objects, &rockets_pool);
        RenderComponent * player_render = new RenderComponent();
        player_render->Create(engine, player, &game_objects, "data/cursor.png");

        player->Create();
        player->AddComponent(player_behaviour);
        player->AddComponent(player_render);
        player->AddReceiver(this);
        game_objects.insert(player);

        enemy = new Enemy();
        EnemyBehaviourComponent * enemy_behaviour = new EnemyBehaviourComponent();
        enemy_behaviour->Create(engine, enemy, &game_objects, &missiles_pool);
        enemy->Create();
        enemy->AddComponent(enemy_behaviour);
        enemy->AddReceiver(this);
        game_objects.insert(enemy);

        rockets_pool.Create(30);
        for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++){
            RocketBehaviourComponent * behaviour = new RocketBehaviourComponent();
            behaviour->Create(engine, *rocket, &game_objects, &explosions_pool);
            //RenderComponent * render = new RenderComponent();
            //render->Create(engine, *rocket, &game_objects, "data/missile.png");
            RigidBodyComponent * rigidBodyComponent = new RigidBodyComponent();
            rigidBodyComponent->Create(engine, *rocket, &game_objects);

            (*rocket)->Create();
            (*rocket)->AddComponent(behaviour);
            //(*rocket)->AddComponent(render);
            (*rocket)->AddComponent(rigidBodyComponent);
        }

        explosions_pool.Create(30);
        for (auto explosion = explosions_pool.pool.begin(); explosion != explosions_pool.pool.end(); explosion++){
            ExplosionBehaviourComponent * behaviour = new ExplosionBehaviourComponent();
            behaviour->Create(engine, *explosion, &game_objects);
            CollideComponent * collide = new CollideComponent();
            collide->Create(engine, *explosion, &game_objects, (ObjectPool<GameObject>*) &missiles_pool);

            (*explosion)->Create();
            (*explosion)->AddComponent(behaviour);
            (*explosion)->AddComponent(collide);
            (*explosion)->AddReceiver(this);
        }

        missiles_pool.Create(10);
        for (auto missile = missiles_pool.pool.begin(); missile != missiles_pool.pool.end(); missile++){
            MissileBehaviourComponent * behaviour = new MissileBehaviourComponent();
            behaviour->Create(engine, *missile, &game_objects);
            RigidBodyComponent * rigid = new RigidBodyComponent();
            rigid->Create(engine, *missile, &game_objects);
            //CollideComponent * collide = new CollideComponent();
            //collide->Create(engine, *missile, &game_objects, (ObjectPool<GameObject>*) &explosions_pool);

            (*missile)->Create();
            (*missile)->AddComponent(behaviour);
            (*missile)->AddComponent(rigid);
            //(*missile)->AddComponent(collide);
            (*missile)->AddReceiver(this);
        }

        town_pool.Create(6);
        for (auto town = town_pool.pool.begin(); town != town_pool.pool.end(); town++){
            RenderComponent * render = new RenderComponent();
            render->Create(engine, *town, &game_objects, "data/town.png");
            CollideComponent * collide = new CollideComponent();
            collide->Create(engine, *town, &game_objects, (ObjectPool<GameObject>*) &missiles_pool);
            TownBehaviourComponent * behaviour = new TownBehaviourComponent();
            behaviour->Create(engine, *town, &game_objects);

            (*town)->Create();
            (*town)->AddComponent(render);
            (*town)->AddComponent(collide);
            (*town)->AddComponent(behaviour);
            (*town)->AddReceiver(this);
            game_objects.insert(*town);
        }

        silo_pool.Create(3);
        for (auto silo = silo_pool.pool.begin(); silo != silo_pool.pool.end(); silo++){
            RenderComponent * render = new RenderComponent();
            render->Create(engine, *silo, &game_objects, "data/silo.png");
            CollideComponent * collide = new CollideComponent();
            collide->Create(engine, *silo, &game_objects, (ObjectPool<GameObject>*) &missiles_pool);
            TownBehaviourComponent * behaviour = new TownBehaviourComponent();
            behaviour->Create(engine, *silo, &game_objects);

            (*silo)->Create();
            (*silo)->AddComponent(render);
            (*silo)->AddComponent(collide);
            (*silo)->AddComponent(behaviour);
            (*silo)->AddReceiver(this);
            game_objects.insert(*silo);
        }

        missile_sprite = engine->createSprite("data/missile.png");
        score = 0;
    }

    virtual void Init(){
        player->Init();
        enemy->Init();
        int i = 0;

        for (auto silo = silo_pool.pool.begin(); silo != silo_pool.pool.end(); silo++){
            (*silo)->Init((WINDOW_WIDTH/2 * i) -16 *i);
            if (i < 2){
                for (int j = 1; j < 4; j++){
                    Town * town = town_pool.FirstAvailable();
                    town->Init((*silo)->horizontalPos + j * 76);
                }
            }
            i++;
        }

        enabled = true;
        game_over = false;
        level_win = false;
    }

    virtual void Update(float dt){
        AvancezLib::KeyStatus keys;
        engine->getKeyStatus(keys);

        if (keys.esc){
            destroy();
            engine->quit();
        }

        if (isLevelWin()){
            //SDL_Log("Win");
        }

        if (isGameOver()){
            dt = 0.f;
        }

        for (auto go = game_objects.begin(); go != game_objects.end(); go++){
            (*go)->Update(dt);
        }
    }

    virtual void Draw(){
        int i = 0;
        for (auto silo = silo_pool.pool.begin(); silo != silo_pool.pool.end(); silo++){
            for (int j = 0; j < player->GetComponent<PlayerBehaviourComponent*>()->GetLeftInSilo(i); j++){
                missile_sprite->draw((*silo)->horizontalPos + j * 5, (*silo)->verticalPos + 16);
            }
            i++;
        }

        engine->swapBuffers();
        engine->clearWindow();
    }

    virtual void Receive(Message m){
        if (m == LEVEL_WIN){
            missiles--;
            SDL_Log("missiles %i", missiles);
            if (missiles == 0)
                level_win = true;   
        }
    }

    void newLevel(){

    }

    bool isLevelWin(){
        return level_win;
    }

    bool isGameOver(){
        return game_over;
    }

    unsigned int Score(){
        return score;
    }

    virtual void destroy(){
        SDL_Log("Game::Destroy");

        for (auto go = game_objects.begin(); go != game_objects.end(); go++){
            (*go)->Destroy();
        }

        rockets_pool.Destroy();
        delete player;
    }
};