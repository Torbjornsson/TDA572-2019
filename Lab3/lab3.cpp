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
	int deltaTime = 0;
	int lastTime = engine.getElapsedTime();
	bool red = false;
	while (engine.update())
	{ 
		//Gameloop here...

		//start clock
		deltaTime = engine.getElapsedTime() - lastTime;

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

		/*fps counter				
		if (deltaTime != 0){
			std::cout << 1000 / deltaTime << std::endl;
		}
		*/

		//lastTime before sleep
		lastTime = engine.getElapsedTime();
		usleep(16000 - deltaTime);
		
	}
	
	//Clean up here...
	engine.destroy();
	
	return 0;
}