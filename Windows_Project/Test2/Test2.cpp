#include "pch.h"
#include "stdio.h"
#include <iostream>
#include <set>

#include "vector2D.h"
#include "avancezlib.h"

#include "Object_pool.h"
#include "Component.h"
#include "GameObject.h"

//Global constants and variables for controlling the game (needs to be here)

const float FIRE_TIME_INTERVAL = .5f;
const float ROCKET_SPEED = 120.f;
const static int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;

float game_speed = 1.f;
#include "Silo.h"
#include "Explosion.h"
#include "Rocket.h"
#include "player.h"

#include "Missile.h"
#include "Enemy.h"

#include "Town.h"
#include "game.h"

int main(int argc, char* argv[]) {
	//Window size

	//init engine
	AvancezLib engine;

	engine.init(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Mouse
	int x, y, tx, ty;

	//Start game
	Game game;
	game.Create(&engine);
	game.Init();

	float lastTime = engine.getElapsedTime();

	//Game loop
	while (true) {
		//Calculate time since last frame
		float newTime = engine.getElapsedTime();
		float dt = newTime - lastTime;
		lastTime = engine.getElapsedTime();
		dt = dt * game_speed;

		engine.processInput();
		game.Update(dt);
		game.Draw();
	}

	//cleanup
	game.destroy();
	engine.destroy();
	return 0;
}