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
	int num_frames = 0;
	float avg_fps = 0;
	float deltaTime = 0;
	float sum_delta = 0;
	const static int FPS = 60;
	const static float MS_Frame = 1000/FPS;
	float lastTime = engine.getElapsedTime();


    //Game loop
    while(true){
		
        SDL_GetMouseState(&x, &y);
        
        //Handle key events
        AvancezLib::KeyStatus key;
		engine.getKeyStatus(key);

		if (key.fire1){
		    engine.drawCircle(x, y, 20);
            tx = x;
            ty = y;
        }

        //average FPS counter			
		if (num_frames == 80){
			avg_fps = (((float)num_frames) / sum_delta);
			num_frames = 0;
			sum_delta = 0.f;
		}
		//Set text and print
		sprintf(msg, "%.3f fps", avg_fps);
		engine.drawText(0, 0, msg);
		

		
		//Sleep to keep fps lock to 60 fps
		//SDL_Delay(std::max((MS_Frame - deltaTime), 0.f));	

		//Calculate time since last frame
		deltaTime = engine.getElapsedTime() - lastTime;
		lastTime = engine.getElapsedTime();
		deltaTime = deltaTime * game_speed;

		//To calculate average FPS
		num_frames++;	
		sum_delta += deltaTime;
		engine.processInput();
		game.Update(deltaTime);
		game.Draw();
    }

    //cleanup
	game.destroy();
    engine.destroy();
    return 0;
}