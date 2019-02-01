#include "avancezlib.h"
#include <iostream>

int main(int argc, char* argv[])
{
	AvancezLib engine;
	//Initialize here...
	//window and engine
	int width = 640;
	int height = 480;
	engine.init(width, height);

	//FPS
	int num_frames = 0;
	float avg_fps = 0;
	int deltaTime = 0;
	int sum_delta = 0;
	int FPS = 60;
	int lastTime = engine.getElapsedTime();
	char msg[256];

	//player
	Sprite * player = engine.createSprite("enemy_0.bmp");
	int x = 0;
	int y = 180;

	//color
	int i = 0;
	bool red = false;
	
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
			red = true;
		else if (i == 0)
			red = false;
			i++;
		else
			i++;

		//Handle keys
		AvancezLib::KeyStatus key;
		engine.getKeyStatus(key);

		if (key.fire)
			SDL_Log("fire\n");

		if (key.left){
			SDL_Log("left\n");
			if(x > 0)
				x-=10;
		}

		if (key.right){
			SDL_Log("right\n");
			if(x < 400)
				x+=10;
		}

		//drawing sprite
		player->draw(x, y);
		
		//fps counter			
		num_frames++;	
		if (sum_delta > 100){
			avg_fps = ((float)num_frames / sum_delta) * 1000;
			num_frames = 0;
			sum_delta = 0;
		}
		sprintf(msg, "%.3f fps", avg_fps);
		engine.drawText(0, 0, msg);
		
		//Sleep to keep fps
		SDL_Delay(std::max((1000/FPS) - deltaTime, 0));	
	}

	//Clean up here...
	player->destroy();
	engine.destroy();
	
	return 0;
}