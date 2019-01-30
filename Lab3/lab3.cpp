#include "avancezlib.h"
#include <iostream>
#include "unistd.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
	AvancezLib engine;
	//Initialize here...
	engine.init(400,400);
	int i = 0;
	int lastTime = engine.getElapsedTime();
	bool red = false;
	while (engine.update())
	{ 
		//Gameloop here...
		int currentTime = engine.getElapsedTime();
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
		
		
		//std::cout << currentTime - lastTime;
		usleep(10000 -(currentTime - lastTime));
		lastTime = currentTime;
	}
	
	//Clean up here...
	engine.destroy();
	
	return 0;
}