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
    font = TTF_OpenFont("space_invaders.ttf", 12);
    if (font == NULL){
        		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
                return false;
    }

    int was_init = TTF_WasInit();
 
    if (was_init == 1)
        std::cout << "SDL_ttf init success" << std::endl;
        // SDL_ttf was already initialized

    else if (was_init == 0)
        std::cout << "error init" << std::endl;
        // SDL_ttf was not already initialized

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
    key.fire = false;
    key.left = false;
    key.right = false;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return false;
        }

        if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                case SDLK_q:
                    return false;
                    break;
                case SDLK_SPACE:
                    return key.fire = true;
                    break;
                case SDLK_LEFT:
                    return key.left = true;
                    break;
                case SDLK_RIGHT:
                    return key.right = true;
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
    SDL_Color black = {0, 0, 0};
    
    SDL_Surface *fsurface; 
    fsurface = TTF_RenderText_Solid(font, msg, black);
    
    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, fsurface);

    int width, height = 0;
    SDL_QueryTexture(msgTexture, NULL, NULL, &width, &height);
    
    SDL_Rect rect = {x, y, width, height};

    SDL_RenderCopy(renderer, msgTexture, NULL, &rect);

    SDL_DestroyTexture(msgTexture);
    SDL_FreeSurface(fsurface);
}

void AvancezLib::getKeyStatus(KeyStatus & keys){
    keys.fire = key.fire;
    keys.left = key.left;
    keys.right = key.right;
}

Sprite * AvancezLib::createSprite(const char * name){
    SDL_Surface* surface = SDL_LoadBMP(name);
    if(surface == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "unable to load image", name, SDL_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "unable to crate texture", name, SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(surface);

    Sprite * sprite = new Sprite(renderer, texture);

    return sprite;

}

Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture){
    this->renderer = renderer;
    this->texture = texture;
}

void Sprite::draw(int x, int y){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Sprite::destroy(){
    SDL_DestroyTexture(texture);
}