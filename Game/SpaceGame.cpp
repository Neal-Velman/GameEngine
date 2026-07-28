#include "SpaceGame.h"
#include "Engine.h"

bool SpaceGame::Initialize() {
    Game::Initialize();
    m_scene = new nu::Scene();
    return true;
}

using namespace nu;
void SpaceGame::Update(float dt) {
    switch (m_gameState)
    {
    case GameState::TITLE:
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::START_GAME;
        }
        break;
    case GameState::START_GAME:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::START_LEVEL;
        break;
    case GameState::START_LEVEL:
        break;
    case GameState::GAME:
        break;
    case GameState::GAME_OVER:
        break;
    default:
        break;
    }
    Game::Update(dt);
}

void SpaceGame::Draw(const nu::Renderer& renderer) {
    switch (m_gameState) {
    case GameState::TITLE:
        break;
    case GameState::START_GAME:
        break;
    case GameState::START_LEVEL:
        break;
    case GameState::GAME:
        break;
    case GameState::GAME_OVER:
        break;
    default:
        break;
    }

    Game::Draw(renderer);
}
