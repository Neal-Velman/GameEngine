#include <iostream>
#include "Engine.h"
#include "SDL3/SDL.h"

int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);


    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        for (int i = 0; i < 1000; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1280, rand() % 1024);
        }

		renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
        renderer.DrawFillRect(40, 40, 50, 50);

        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderDebugText(renderer, 10, 10, "Hello World!");

        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}

