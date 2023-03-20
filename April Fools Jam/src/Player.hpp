#pragma once

#include "Equinox/Equinox.hpp"

class Player
{
private:

	eq::Physics::BoxShape* m_Collider;

	int jumps = 1;

public:
	Player(eq::Math::Vector2 position);

	eq::Physics::BoxShape* getCollider() { return m_Collider; }
	void setCollider(eq::Physics::BoxShape* collider) { delete m_Collider; m_Collider = collider; }

	void applyForce(eq::Math::Vector2 force) { m_Collider->applyForce(force * m_Collider->getMass()); }

	bool hasJumps() { return jumps > 0; }
	void setJumps(int jumps) { this->jumps = jumps; }
	
};