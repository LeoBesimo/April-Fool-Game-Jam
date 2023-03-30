#pragma once

#include "Equinox/Equinox.hpp"
#include "Player.hpp"
#include "Level/Level.hpp"

class Game
{
private:

	eq::Physics::PhysicsWorld m_World = eq::Physics::PhysicsWorld(eq::Math::Vector2(5000,8000));
	std::shared_ptr<eq::Camera> m_Camera;

	Level level = Level(m_World);

	Platform* platform;

	Player* m_Player;


public:
	Game();
	void update(float delta);

	void render();

	void start();
};