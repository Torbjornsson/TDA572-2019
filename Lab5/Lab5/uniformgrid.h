#pragma once

#include "game_object.h"

class GameObject;

class UniformGrid{
    

public:
    std::vector<std::vector<GameObject*> *> grid;
    void Create(int size){
        std::vector<GameObject*> *v = new std::vector<GameObject *>();
        grid = std::vector<std::vector<GameObject *>*>(size, v);

    }

    void Init(){
        SDL_Log("UniformGrid::Init");
    }

    void Update(std::set<GameObject*> game_objects){
        //Clear grid

        for (std::vector<GameObject*>* game_objects0 : grid){
            game_objects0->clear();
        }

        for (auto go = game_objects.begin(); go != game_objects.end(); go++){
            //check if position is 0
            int xpos, ypos;            
            
            if ((*go)->position.x <= 0)
                xpos = 0;
            else
                xpos = floor((*go)->position.x / 32);

            if ((*go)->position.y <= 0)
                ypos = 0;

            else
                ypos = floor((*go)->position.y / 32) * 20;
            
            grid[xpos + ypos]->push_back((*go));
            
        }

    }
};