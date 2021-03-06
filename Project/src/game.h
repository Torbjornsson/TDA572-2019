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

    ObjectPool<GameObject> towns;

   public:
    virtual void Create(AvancezLib* engine){
        SDL_Log("Game::Create");

        this->engine = engine;

        player = new Player();
        PlayerBehaviourComponent * player_behaviour = new PlayerBehaviourComponent();
        player_behaviour->Create(engine, player, &game_objects, &rockets_pool, &silo_pool);
        RenderComponent * player_render = new RenderComponent();
        player_render->Create(engine, player, &game_objects, "data/cursor.png");

        player->Create();
        player->AddComponent(player_behaviour);
        player->AddComponent(player_render);
        player->AddReceiver(this);
        game_objects.insert(player);

        enemy = new Enemy();
        EnemyBehaviourComponent * enemy_behaviour = new EnemyBehaviourComponent();
        enemy_behaviour->Create(engine, enemy, &game_objects, &missiles_pool, &towns);
        enemy->Create();
        enemy->AddComponent(enemy_behaviour);
        enemy->AddReceiver(this);
        game_objects.insert(enemy);
        towns.Create(9);

        rockets_pool.Create(30);
        for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++){
            RocketBehaviourComponent * behaviour = new RocketBehaviourComponent();
            behaviour->Create(engine, *rocket, &game_objects, &explosions_pool);
            RigidBodyComponent * rigidBodyComponent = new RigidBodyComponent();
            rigidBodyComponent->Create(engine, *rocket, &game_objects);

            (*rocket)->Create();
            (*rocket)->AddComponent(behaviour);
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

            (*missile)->Create();
            (*missile)->AddComponent(behaviour);
            (*missile)->AddComponent(rigid);
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
            towns.pool.push_back(*town);
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
            towns.pool.push_back(*silo);
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

        if (isLevelWin() && !isGameOver()){
            int i = 0;
            for (auto go = town_pool.pool.begin(); go != town_pool.pool.end(); go++){
                if ((*go)->enabled)
                    i++;
            }
            int j = 0;
            for (int n = 0; n < 3; n++){
                j += player->GetComponent<PlayerBehaviourComponent*>()->GetLeftInSilo(n);
            }
            score += 100 * i + 5 * j;
            newLevel();
        }

        if (isGameOver()){
            dt = 0.f;
        }

        if (!isGameOver()){
        for (auto go = game_objects.begin(); go != game_objects.end(); go++){
            (*go)->Update(dt);
        }}
    }

    virtual void Draw(){
        char msg[1024];
		sprintf(msg, "%07d", Score());
		engine->drawText(300, 32, msg);

        if (isGameOver()){
			sprintf(msg, "*** G A M E  O V E R ***");
			engine->drawText(250, 8, msg);
		}

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
        if (m == MISSILE_HIT)
            score += 25;

        if (m == GAME_OVER){
            if (towns.SelectRandom() == NULL)
                game_over = true;
        }

        if (m == LEVEL_WIN){
            missiles--;
            if (missiles == 0)
                level_win = true;   
        }
    }

    void newLevel(){
        player->GetComponent<PlayerBehaviourComponent*>()->Reset();
        enemy->GetComponent<EnemyBehaviourComponent*>()->Reset();
        for (auto silo = silo_pool.pool.begin(); silo != silo_pool.pool.end(); silo++){
            (*silo)->enabled = true;
        }
        level_win = false;
        missiles = 10;
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
        explosions_pool.Destroy();
        missiles_pool.Destroy();
        town_pool.Destroy();
        silo_pool.Destroy();
        towns.Destroy();
        missile_sprite->destroy();

        delete player;
        delete enemy;
    }
};