#include "Engine.h"

int main()
{




    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);


    nu::Input input;
    input.Initialize();

    nu::Time time;

    nu::Mesh mesh{ { { -3, 3 }, { 3, 3 }, { 0, 0 } }, nu::Color{ 0.0f, 0.0f, 0.0f} };

    nu::Actor player{ nu::Transform{ nu::Vector2{ 860.0f, 512.0f }, 0.0f, 50.0f}, std::vector<nu::Mesh>{ mesh } };


    nu::Vector2 position{ 860.0f, 512.0f };
    nu::Vector2 velocity{ 0.0f, 0.0f };
    float speed = 400.0f;
    std::vector<nu::Vector2> points;

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
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // UPDATE ENGINE
        input.Update();
        time.Tick();

        /*if (input.GetKeyPressed(SDL_SCANCODE_K)) std::cout << "Pressed" << std::endl;
        if (input.GetKeyDown(SDL_SCANCODE_K)) std::cout << "Down" << std::endl;
        if (input.GetKeyReleased(SDL_SCANCODE_K)) std::cout << "Released" << std::endl;

		if (input.GetButtonPressed(nu::Input::MouseButton::LEFT)) std::cout << "Mouse Pressed" << std::endl;
		if (input.GetMouseDown(nu::Input::MouseButton::LEFT)) std::cout << "Mouse Pressed" << std::endl;*/

        if (input.GetMouseDown(nu::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(input.GetMousePosition());
            }
            else {
                nu::Vector2 v = points.back() - input.GetMousePosition();
                if (v.Length() > 10.0f) {
                    points.push_back(input.GetMousePosition());
                }
            }

        }

        if (input.GetButtonPressed(nu::Input::MouseButton::RIGHT)) {
            if (!points.empty()) {
                points.pop_back();
            }
        }
        
        

        nu::Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());
		
        //velocity += (force * time.GetDeltaTime());
        //position += (velocity * time.GetDeltaTime());

        //position.x = nu::math::Wrap(0.0f, 1920.0f, position.x);
        //position.y = nu::math::Wrap(0.0f, 1024.0f, position.y);

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i+1].y);
            renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // Character
        player.Draw(renderer);
        //renderer.SetColor(1.0f, 1.0f, 1.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        renderer.Present();
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}