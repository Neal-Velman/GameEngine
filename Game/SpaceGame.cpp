#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

bool SpaceGame::Initialize() {
    Game::Initialize();
    m_gameState = GameState::TITLE;
    m_scene = new nu::Scene();
    m_scene->SetGame(this);

    m_titleFont = new nu::Font();
    m_titleFont->Load("Fonts/Jersey10Charted-Regular.ttf", 64);

    m_titleText = new nu::Text(m_titleFont);
    m_titleText->Create(nu::Engine::Get().GetRenderer(), "Hello World", nu::Color{ 1.0f, 1.0f, 1.0f });

    m_gameFont = new nu::Font();
    m_gameFont->Load("Fonts/Jersey10Charted-Regular.ttf", 32);

    m_scoreText = new nu::Text(m_gameFont);
    m_livesText = new nu::Text(m_gameFont);

    return true;
}

using namespace nu;
void SpaceGame::Update(float dt) {
    switch (m_gameState) {
    case GameState::TITLE:
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::START_GAME;
        }
        break;
    case GameState::START_GAME:
        m_score = 0;
        m_lives = 3;
        m_spawnTime = 5.0f;
        m_stateTimer = 0.5f;
        m_gameState = GameState::START_LEVEL;
        break;
    case GameState::START_LEVEL:
        m_scene->RemoveAllActors();
        SpawnPlayer();
        m_spawnTime = 5.0f;
        m_gameState = GameState::GAME;
        break;
    case GameState::GAME:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0.0f) {
            m_spawnTimer = nu::RandomFloat(3.0f, 5.0f);
            SpawnEnemy();
            m_spawnCount++;
            if (m_spawnCount > 5) {
                m_spawnCount = 0;
                m_spawnTime -= 0.5f;
            }
        }
        break;
    case GameState::GAME_OVER:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_scene->RemoveAllActors();
            m_gameState = GameState::TITLE;
        }
        break;
    default:
        break;
    }
    Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer) {
    switch (m_gameState) {
    case GameState::TITLE:
        m_titleText->Create(nu::Engine::Get().GetRenderer(), "Hello World", nu::Color{ 1.0f, 1.0f, 1.0f });
        m_titleText->Draw(renderer, 400, 400);
        break;
    case GameState::START_GAME:
        break;
    case GameState::START_LEVEL:
        break;
    case GameState::GAME:
        m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
        m_scoreText->Draw(renderer, 30, 30);

        m_scoreText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
        m_scoreText->Draw(renderer, (float)renderer.GetWidth() - 160, (float)30);
        break;
    case GameState::GAME_OVER:
        break;
    default:
        break;
    }

    Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead() {
    m_lives--;
    m_gameState = (m_lives == 0) ? GameState::GAME_OVER : GameState::START_LEVEL;

    //if (m_lives == 0) {
    //    m_gameState = GameState::GAME_OVER;
    //}
    //else {
    //    m_gameState = GameState::START_LEVEL;
    //}
}

void SpaceGame::SpawnPlayer() {

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = Assets::playerModel;
    playerDesc.transform = nu::Transform{ nu::Vector2 { 860.0f, 512.0f }, 0.0f, 50.0f };
    playerDesc.speed = 600.0f;
    playerDesc.damping = 1.5f;

    Player* player = new Player{ playerDesc };
    m_scene->AddActor(player);
}

void SpaceGame::SpawnEnemy() {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = Assets::playerModel;
        enemyDesc.transform = nu::Transform{ nu::Vector2 { nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 180.0f, 25.0f };
        enemyDesc.speed = nu::RandomFloat(200.0f, 400.0f);
        enemyDesc.damping = 1.5f;

        Enemy* enemy = new Enemy{ enemyDesc };
        m_scene->AddActor(enemy);
}
