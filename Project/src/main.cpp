#include "stdio.h"
#include <iostream>
#include <set>

#include "avancezlib.h"

#include "Object_pool.h"
#include "Component.h"
#include "GameObject.h"

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

    //FPS
    char msg[256];
	int num_frames = 0;
	float avg_fps = 0;
	int deltaTime = 0;
	int sum_delta = 0;
	const static int FPS = 60;
	const static int MS_Frame = 1000/FPS;
	int lastTime = engine.getElapsedTime();

    //Game loop
    while(true){
		
        SDL_GetMouseState(&x, &y);
        engine.drawCircle(x, y, 20);
        
        //Handle key events
        AvancezLib::KeyStatus key;
		engine.getKeyStatus(key);

		if (key.fire1){
		    engine.drawLine(width/2, height, x, y);
            tx = x;
            ty = y;
        }

        //average FPS counter			
		if (num_frames == 10){
			avg_fps = (((float)num_frames * 1000) / sum_delta);
			num_frames = 0;
			sum_delta = 0;
		}
		//Set text and print
		sprintf(msg, "%.3f fps", avg_fps);
		engine.drawText(0, 0, msg);
		

		engine.processInput();
		//Sleep to keep fps
		SDL_Delay(std::max((MS_Frame - (engine.getElapsedTime() - lastTime)), 0));	

		//Calculate time since last frame
		deltaTime = engine.getElapsedTime() - lastTime;
		lastTime = engine.getElapsedTime();

		//To calculate average FPS
		num_frames++;	
		sum_delta += deltaTime;
    }

    //cleanup
    engine.destroy();
    return 0;
}