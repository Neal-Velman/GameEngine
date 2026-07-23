#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "Bullet.h"
#include "Assets.h"

void Player::Update(float dt) {

    // movement
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust =  m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f) * thrust;
    AddVelocity(velocity * dt);

    // fire
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        BulletDesc desc;
        desc.name = "Bullet";
        desc.tag = "Bullet";
        desc.model = Assets::bulletModel;
        desc.transform = m_transform;
        desc.speed = 400.0f;
        desc.lifespan = 3.0f;

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(bullet);
    }

    Actor::Update(dt);
}