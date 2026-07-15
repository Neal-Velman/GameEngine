#include "Engine.h"
#include "Player.h"

#include <iostream>
#include <vector>

int main()
{
    // INITIALIZATION
    nu::engine.Initialize();

    nu::Mesh mesh{ { { 2, 0 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.0f, 0.0f, 0.0f } };
    Player player{ 400.0f, nu::Transform { nu::Vector2 { 860.0f, 512.0f }, 0.0f, 50.0f }, std::vector<nu::Mesh> { mesh } };

    std::vector<nu::Vector2> points;

    // MAIN LOOP
    bool quit = false;

    // UPDATE
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // UPDATE ENGINE
        nu::engine.Update();

        player.SetRotation(player.GetTransform().rotation + (90.0f * nu::engine.GetTime().GetDeltaTime()));
        player.Update(nu::engine.GetTime().GetDeltaTime());


        if (nu::engine.GetInput().GetMouseDown(nu::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(nu::engine.GetInput().GetMousePosition());
            }
            else {
                nu::Vector2 v = points.back() - nu::engine.GetInput().GetMousePosition();
                if (v.Length() > 10.0f) {
                    points.push_back(nu::engine.GetInput().GetMousePosition());
                }
            }

        }

        if (nu::engine.GetInput().GetButtonPressed(nu::Input::MouseButton::RIGHT)) {
            if (!points.empty()) {
                points.pop_back();
            }
        }
        

        // RENDER
        nu::engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        nu::engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            nu::engine.GetRenderer().SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            nu::engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i+1].y);
            nu::engine.GetRenderer().DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // Character
        player.Draw(nu::engine.GetRenderer());

        nu::engine.GetRenderer().Present();
    }

    // SHUTDOWN
    nu::engine.Shutdown();
    

    return 0;
}