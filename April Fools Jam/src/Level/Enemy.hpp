#pragma once

#include <Equinox/Equinox.hpp>

class Enemy:
	public eq::Physics::BoxShape
{
private:
	eq::BitmapTexture spriteSheet;
	std::vector<eq::Sprite> animationRight;
	std::vector<eq::Sprite> animationLeft;

	long animationFrame = 0;
	int animationStep = 0;

	bool lastDirectionLeft = false;
	int cooldown = 0;
	bool enableTimer = true;

	eq::Math::Vector2 moveForce;

public:
	Enemy(eq::Math::Vector2 position);

	void update();

	eq::Sprite getAnimationFrame();
};