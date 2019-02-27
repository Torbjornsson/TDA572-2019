#include "stdio.h"
#include <iostream>
#include <set>

#include "avancezlib.h"

#include "Object_pool.h"
#include "Component.h"
#include "GameObject.h"

//Global constants and variables for controlling the game (needs to be here)

const float FIRE_TIME_INTERVAL = .05f;

float game_speed = 1.f;

#include "Rocket.h"
#include "player.h"

#include "game.h"

int main(int argc, char* argv[]){
    //Window size
    const static int width = 640, height = 480;

    //init engine
    AvancezLib engine;

    engine.init(width, height);

    //Mouse
    int x, y, tx, ty;

	//Start game
	Game game;
	game.Create(&engine);
	game.Init();

    //FPS
    char msg[256];
	float deltaTime = 0;
	float lastTime = engine.getElapsedTime();


    //Game loop
    while(true){
		//Calculate time since last frame
		deltaTime = engine.getElapsedTime() - lastTime;
		lastTime = engine.getElapsedTime();
		deltaTime = deltaTime * game_speed;

		engine.processInput();
		game.Update(deltaTime);
		game.Draw();
    }

    //cleanup
	game.destroy();
    engine.destroy();
    return 0;
}