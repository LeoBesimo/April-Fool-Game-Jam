#pragma once

#include "Equinox/Equinox.hpp"

#define PLAYER_TAG_ID 1

class Player:
	public eq::Physics::BoxShape
{
private:

	eq::BitmapTexture m_SpriteSheet;
	std::vector<eq::Sprite> m_AnimationRight;
	std::vector<eq::Sprite> m_AnimationLeft;


	//eq::Physics::BoxShape* m_Collider;

	int jumps = 1;
	long animationFrame = 0;
	int animationStep = 0;
	bool onGround = false;
	bool lastDirectionLeft = false;

public:
	Player(eq::Math::Vector2 position);

	bool hasJumps() { return jumps > 0; }
	int getJumpCount() { return jumps; }
	void setJumps(int jumps) { this->jumps = jumps; }
	bool isOnGround() { return onGround; }
	void setOnGround(bool onGround) { this->onGround = onGround; }

	void update();

	eq::Sprite getAnimationFrame();
};