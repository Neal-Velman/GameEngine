#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"

namespace nu {
	
    void Actor::Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.975f;

        m_transform.position.x = math::Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = math::Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const nu::Renderer& renderer) const {
        renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

}