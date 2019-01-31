#include "avancezlib.h"
#include <iostream>
#include "stdio.h"

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

    TTF_Init();

    int was_init = TTF_WasInit();
 
    if (was_init == 1)
        std::cout << "SDL_ttf init success" << std::endl;
        // SDL_ttf was already initialized

    else if (was_init == 0)
        std::cout << "error init" << std::endl;
        // SDL_ttf was not already initialized

    const SDL_version *linked_version = TTF_Linked_Version();
    SDL_version compiled_version;   
    SDL_TTF_VERSION(&compiled_version);
    if (linked_version != NULL)
        std::cout << "version" << std::endl;

    std::cout << "Linked version:\n"
        << linked_version->major << "." << linked_version->minor << "." << linked_version->patch;
 
    std::cout << "Compiled version:\n"
        << compiled_version.major << "." << compiled_version.minor << "." << compiled_version.patch << std::endl << std::endl;

    font = TTF_OpenFont("Ubuntu-B.ttf", 12);
    if (!font){
        std::cout << TTF_GetError();
        return false;
    }

    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    return true;
}

void AvancezLib::destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
}

void AvancezLib::setColor(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

bool AvancezLib::update(){
    
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
    
    
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);  

    return true;
}

int AvancezLib::getElapsedTime(){
    return SDL_GetTicks();
}

void AvancezLib::drawText(int x, int y, const char* msg){
    
    std::cout << font << std::endl;
    SDL_Color black = {0, 0, 0};
    
    SDL_Surface *fsurface; 
    fsurface = TTF_RenderText_Solid(font, msg, black);
    std::cout << msg << std::endl;
    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, fsurface);

    int width, height = 0;
    SDL_QueryTexture(msgTexture, NULL, NULL, &width, &height);
    std::cout << width << ", " << height << std::endl;
    SDL_Rect rect = {x, y, width, height};

    SDL_RenderCopy(renderer, msgTexture, NULL, &rect);

    SDL_DestroyTexture(msgTexture);
    SDL_FreeSurface(fsurface);
}