#include "avancezlib.h"
#include <iostream>

int main(int argc, char* argv[])
{
	AvancezLib engine;
	//Initialize here...
	engine.init(400,400);
	int i = 0;
	int num_frames = 0;
	float avg_fps = 0;
	int deltaTime = 0;
	int sum_delta = 0;
	int FPS = 60;
	int lastTime = engine.getElapsedTime();
	bool red = false;
	char msg[256];

	Sprite * player = engine.createSprite("enemy_0.bmp");

	while (engine.update())
	{ 
		//Gameloop here...

		//start clock
		deltaTime = engine.getElapsedTime() - lastTime;
		lastTime = engine.getElapsedTime();

		sum_delta += deltaTime;
		//shift colors
		engine.setColor(i, 0, 255-i, 0);

		if (red && i >0)
			i--;
		else if (i == 255)
		{
			red = true;
		}
		else if (i == 0){
			red = false;
			i++;
		}
		else
		{
			i++;
		}

		player->draw(200, 200);
		
		//fps counter			
		num_frames++;	
		if (sum_delta > 100){
			avg_fps = ((float)num_frames / sum_delta) * 1000;
			num_frames = 0;
			sum_delta = 0;
		}
		sprintf(msg, "%.3f fps", avg_fps);
		engine.drawText(0, 0, msg);
		//lastTime before sleep
		
		SDL_Delay(std::max((1000/FPS) - deltaTime, 0));	
	}
	//Clean up here...
	player->destroy();
	engine.destroy();
	
	return 0;
}