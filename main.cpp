#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#undef main
#include <iostream>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;

int tile_width = 32;

int main()
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Este es mi mensaje", 100, 100, 640/*WIDTH*/, 320/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    SDL_Texture *texture_piso, *texture_pared;
    SDL_Texture *texture_mago;
    SDL_Texture *texture_cursor;
    SDL_Texture *texture_seleccionado;
    SDL_Rect rectangulo;
    SDL_Rect personaje;
    texture_piso = IMG_LoadTexture(renderer,"piso.png");
    texture_pared = IMG_LoadTexture(renderer,"pared.png");
    texture_mago = IMG_LoadTexture(renderer,"mago.png");
    texture_cursor = IMG_LoadTexture(renderer,"cursor.png");
    texture_seleccionado = IMG_LoadTexture(renderer,"seleccionado.png");

    rectangulo.h = tile_width;
    rectangulo.w = tile_width;
    personaje.h = tile_width;
    personaje.w = tile_width;

    int arr[10][20]={
                    {0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1},
                    {0,1,0,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,1,1},
                    {0,1,0,0,0,0,1,0,1,0,0,1,1,0,0,0,0,0,1,1},
                    {0,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,0,0,1,1},
                    {0,0,0,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,1},
                    {0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1},
                    {0,1,0,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,1,1},
                    {0,1,0,0,0,0,1,0,1,0,0,1,1,0,0,0,0,0,1,1},
                    {0,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,0,0,1,1},
                    {0,0,0,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,1}};

    int frame = 0;
    int frame_anterior = 0;
    int cursor_x = 0;
    int cursor_y = 0;
    personaje.x=0;
    personaje.y=0;
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_w)
                {
                    cursor_y--;
                }
                if(Event.key.keysym.sym == SDLK_a)
                {
                    cursor_x--;
                }
                if(Event.key.keysym.sym == SDLK_s)
                {
                    cursor_y++;
                }
                if(Event.key.keysym.sym == SDLK_d)
                {
                    cursor_x++;
                }
                if(Event.key.keysym.sym ==SDLK_SPACE)
                {
                    if(arr[cursor_y][cursor_x]==0){
                    personaje.x=cursor_x*tile_width;
                    personaje.y=cursor_y*tile_width;
                    }
                }
            }
        }
        for(int x=0;x<20;x++)
        {
            for(int y=0;y<10;y++)
            {
                if(arr[y][x]==1)
                {
                    rectangulo.x = x*tile_width;
                    rectangulo.y = y*tile_width;
                    SDL_RenderCopy(renderer, texture_pared, NULL, &rectangulo);
                }
                else
                {
                    rectangulo.x = x*tile_width;
                    rectangulo.y = y*tile_width;
                    SDL_RenderCopy(renderer, texture_piso, NULL, &rectangulo);
                }
            }
        }
        rectangulo.x = 0;
        rectangulo.y = 0;
        SDL_RenderCopy(renderer, texture_mago, NULL, &personaje);

        rectangulo.x = cursor_x*tile_width;
        rectangulo.y = cursor_y*tile_width;
        SDL_RenderCopy(renderer, texture_cursor, NULL, &rectangulo);

        SDL_RenderPresent(renderer);

        frame++;
        int frame_actual = SDL_GetTicks() - frame_anterior;
        frame_anterior = SDL_GetTicks();
        if(17-frame_actual>0)
            SDL_Delay( 17-frame_actual );
    }

    cout << "Hello world!" << endl;
    return 0;
}
