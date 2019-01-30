#include "avancezlib.h"

bool AvancezLib::init(int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL init failed", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Lab3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL)
        return false;
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        return false;
    }
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    return true;
}

void AvancezLib::destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void AvancezLib::setColor(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

bool AvancezLib::update(){
    
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);  
    
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return false;
        }

        if(event.type == SDL_KEYUP){
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                case SDLK_q:
                    return false;
                    break;
            
                default:
                    break;
            }
        }
    }
    

    return true;
}

int AvancezLib::getElapsedTime(){
    return SDL_GetTicks();
}