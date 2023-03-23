#pragma once

#include "Equinox/Equinox.hpp"

class Player
{
private:

	eq::BitmapTexture m_SpriteSheet;
	eq::Sprite m_AnimationFrame;

	eq::Physics::BoxShape* m_Collider;

	int jumps = 1;
	bool onGround = false;

public:
	Player(eq::Math::Vector2 position);

	eq::Physics::BoxShape* getCollider() { return m_Collider; }
	void setCollider(eq::Physics::BoxShape* collider) { delete m_Collider; m_Collider = collider; }

	void applyForce(eq::Math::Vector2 force) { m_Collider->applyForce(force * m_Collider->getMass()); }

	bool hasJumps() { return jumps > 0; }
	int getJumpCount() { return jumps; }
	void setJumps(int jumps) { this->jumps = jumps; }
	bool isOnGround() { return onGround; }
	void setOnGround(bool onGround) { this->onGround = onGround; }

	void update();

	eq::Sprite getAnimationFrame() { return m_AnimationFrame; }
};