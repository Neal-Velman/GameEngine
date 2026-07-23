#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"
#include "Player.h"

void Enemy::Update(float dt) {

    Player* player = m_scene->GetActorByName<Player>("Player");

    if (player) {

        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * 180.0f / 3.1415926535897932384626433832795f);
        nu::Vector2 forward { 1,0 };
        forward = forward.Rotate(m_transform.rotation * (3.1415926535897932384626433832795f / 180.0f));
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;
    float rotate = 0.0f;

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * 3.1415926535897932384626433832795f / 180.0f) * thrust;
    AddVelocity(velocity * dt);

    Actor::Update(dt);

}