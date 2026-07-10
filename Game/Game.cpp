#include "Engine.h"


struct Transform {
    nu::Vector2 position;
    float rotation;
    float scale;

};

class Actor {
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform{ transform } {}

    void Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.975f;

        m_transform.position.x = nu::math::Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = nu::math::Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Draw(const nu::Renderer& renderer) const {
        renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

    const Transform& GetTransform() const { return m_transform; }

    void SetPosition(const nu::Vector2& position) { m_transform.position = position; }
    void SetRotation(float rotation) { m_transform.rotation = rotation; }
    void SetScale(float scale) { m_transform.scale = scale; }

    const nu::Vector2& GetVelocity() { return m_velocity; }
    void SetVelocity(const nu::Vector2& velocity) { m_velocity = velocity; }

protected:
    Transform m_transform;
    nu::Vector2 m_velocity{ 0,0 };
};

int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);


    nu::Input input;
    input.Initialize();

    nu::Time time;
    Actor player{ Transform{ nu::Vector2{ 860.0f, 512.0f }, 0.0f, 50.0f} };


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