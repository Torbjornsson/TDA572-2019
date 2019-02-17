#pragma once

class Game : public GameObject{
    //the set of all game objects in the game
    std::set<GameObject*> game_objects;

    AvancezLib* engine;

    bool game_over, level_win;

    unsigned int score = 0;

    /*
    Player * player;
    */

   public:
    virtual void Create(AvancezLib* engine){
        //MOVE THIS!!!
        SDL_Log("Game::Create");

        this->engine = engine;

        score = 0;
    }

    virtual void Init(){
        enabled = true;
        game_over = false;
        level_win = false;
    }

    virtual void Update(float dt){

    }

    virtual void Draw(){

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

    }
};