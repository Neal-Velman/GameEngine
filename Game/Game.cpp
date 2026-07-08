#include "Engine.h"

int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);


    nu::Input input;
    input.Initialize();

    nu::Time time;


    nu::Vector2 position{ 860.0f, 512.0f };
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
            points.push_back(input.GetMousePosition());
        }

        nu::Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = +speed;

        position += (velocity * time.GetDeltaTime());

        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();

        for (int i = 0; i < points.size(); i++) {
            renderer.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // Character
        renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        renderer.Present();
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}