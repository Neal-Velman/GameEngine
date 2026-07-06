#include <iostream>
#include <vector>
#include "Engine.h"

int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    //std::cout << sizeof(nu::Vector2) << std::endl;
    nu::Vector2 vel{ 0.5f, 0.0f };
    std::vector<nu::Vector2> v;
    for (int i = 0; i < 300; i++) {

        nu::Vector2 vec{ nu::RandomFloat(1920), nu::RandomFloat(1024) };

        v.push_back(vec);
    }

    // MAIN LOOP
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    // UPDATE
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (int i = 0; i < v.size(); i++) {
            renderer.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }
/*
        for (int i = 0; i < 15; i++) {
            renderer.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            renderer.DrawLine(nu::RandomFloat(1920), nu::RandomFloat(1024), nu::RandomFloat(1920), nu::RandomFloat(1024));
        }

        for (int i = 0; i < 10; i++) {
            renderer.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            renderer.DrawFillRect((i * nu::RandomFloat(1880)) + 40, (i * nu::RandomFloat(984)) + 40, nu::RandomFloat(90) + 10, nu::RandomFloat(90) + 10);
        }

        */

        renderer.Present();
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}

