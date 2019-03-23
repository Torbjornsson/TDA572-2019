    #pragma once

class Game : public GameObject{
    //the set of all game objects in the game
    std::set<GameObject*> game_objects;

    AvancezLib* engine;

    bool game_over, level_win;

    unsigned int score = 0;

    Player * player;
    
    ObjectPool<Rocket> rockets_pool;

   public:
    virtual void Create(AvancezLib* engine){
        //MOVE THIS!!!
        SDL_Log("Game::Create");

        this->engine = engine;

        player = new Player();
        PlayerBehaviourComponent * player_behaviour = new PlayerBehaviourComponent();
        player_behaviour->Create(engine, player, &game_objects, &rockets_pool);
        RenderComponent * player_render = new RenderComponent();
        player_render->Create(engine, player, &game_objects, "data/player.bmp");

        player->Create();
        player->AddComponent(player_behaviour);
        player->AddComponent(player_render);
        player->AddReceiver(this);
        game_objects.insert(player);

        rockets_pool.Create(30);
        for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++){
            RocketBehaviourComponent * behaviour = new RocketBehaviourComponent();
            behaviour->Create(engine, *rocket, &game_objects);
            RenderComponent * render = new RenderComponent();
            render->Create(engine, *rocket, &game_objects, "data/player.bmp");

            (*rocket)->Create();
            (*rocket)->AddComponent(behaviour);
            (*rocket)->AddComponent(render);
        }

        score = 0;
    }

    virtual void Init(){
        player->Init();

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
            SDL_Log("Win");
        }

        if (isGameOver()){
            dt = 0.f;
        }

        for (auto go = game_objects.begin(); go != game_objects.end(); go++){
            (*go)->Update(dt);
        }
    }

    virtual void Draw(){
        engine->swapBuffers();
        engine->clearWindow();
    }

    virtual void Receive(Message m){

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