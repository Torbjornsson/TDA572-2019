#include "avancezlib.h"
#include <iostream>

int main(int argc, char* argv[])
{
	AvancezLib engine;
	//Initialize here...
	//window and engine
	const static int width = 640;
	const static int height = 480;
	engine.init(width, height);

	//FPS
	int num_frames = 0;
	float avg_fps = 0;
	int deltaTime = 0;
	int sum_delta = 0;
	const static int FPS = 60;
	const static int MS_Frame = 1000/FPS;
	int lastTime = engine.getElapsedTime();
	char msg[256];

	//player
	Sprite * player = engine.createSprite("enemy_0.bmp");
	int x = 0;
	int y = 180;
	float velocity = 0.5f;

	//color
	int i = 0;
	bool red = false;
	
	while (engine.update())
	{ 
		//Gameloop here...
	
		//shift colors
		engine.setColor(i, 0, 255-i, 0);

		if (red && i >0)
			i--;
		else if (i == 255){
			red = true;
			i--;
		}
		else if (i == 0){
			red = false;
			i++;
		}
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
				x-= velocity * deltaTime;
		}

		if (key.right){
			SDL_Log("right\n");
			if(x < width)
				x+= velocity * deltaTime;
		}

		//drawing sprite
		player->draw(x, y);
		
		//average FPS counter			
		if (num_frames == 10){
			avg_fps = (((float)num_frames * 1000) / sum_delta);
			num_frames = 0;
			sum_delta = 0;
		}
		//Set text and print
		sprintf(msg, "%.3f fps", avg_fps);
		engine.drawText(0, 0, msg);
		
		//Sleep to keep fps
		SDL_Delay(std::max((MS_Frame - (engine.getElapsedTime() - lastTime)), 0));	

		//Calculate time since last frame
		deltaTime = engine.getElapsedTime() - lastTime;
		lastTime = engine.getElapsedTime();

		//To calculate average FPS
		num_frames++;	
		sum_delta += deltaTime;
	}

	//Clean up here...
	player->destroy();
	engine.destroy();
	
	return 0;
}