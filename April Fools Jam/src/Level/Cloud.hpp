#pragma once

#include "Equinox/Equinox.hpp"

class Cloud :
	public eq::Physics::BoxShape
{
private:
	eq::Sprite cloud;

	bool giveJump = true;

public:

	Cloud(eq::BitmapTexture cloudTexture, eq::Math::Vector2 position);

	bool canGiveJump() { return giveJump; }

	void update(float delta);

	eq::Sprite getSprite() { return cloud; }

};