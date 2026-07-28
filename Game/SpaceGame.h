#pragma once
#include "Game.h"

class SpaceGame : public nu::Game {
public:
	enum class GameState {
		TITLE,
		START_GAME,
		START_LEVEL,
		GAME,
		GAME_OVER
	};
public:

	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) : Game { scene } {}

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(const class nu::Renderer& renderer) override;
private:
	int m_score { 0 };
	int m_lives { 0 };

	GameState m_gameState = GameState::TITLE;
};