#pragma once

#include "Equinox/Equinox.hpp"
#include "Player.hpp"

class Game
{
private:

	eq::Physics::PhysicsWorld m_World = eq::Physics::PhysicsWorld(eq::Math::Vector2(5000,3000));
	std::shared_ptr<eq::Camera> m_Camera;

	Player m_Player = Player(eq::Math::Vector2(200,200));

public:
	Game();
	void update(float delta);

	void render();

	void start();
};