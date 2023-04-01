#pragma once

#include "Equinox/Equinox.hpp"
#include "Player.hpp"
#include "Level/Level.hpp"

class Game
{
private:

	eq::Physics::PhysicsWorld m_World = eq::Physics::PhysicsWorld(eq::Math::Vector2(20000,4000));
	std::shared_ptr<eq::Camera> m_Camera;

	int levelIndex = 0;
	int prevLevel = 0;

	std::vector<Level> levels;

	Platform* platform;

	Player* m_Player;



public:
	Game();
	void update(float delta);

	void render();

	void start();
};