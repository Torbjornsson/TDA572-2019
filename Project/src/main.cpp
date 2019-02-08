#include "avancezlib.h"
#include <iostream>

int main(int argc, char* argv[]){
    //Window size
    const static int width = 640, height = 480;

    //init engine
    AvancezLib engine;

    engine.init(width, height);

    //Game loop
    while(engine.update()){

    }

    //cleanup
    engine.destroy();
    return 0;
}