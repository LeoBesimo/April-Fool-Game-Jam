#pragma once

#include "Equinox/Equinox.hpp"

class Mushroom :
	public eq::Physics::BoxShape
{
private:
	eq::Sprite mushroomSprite;

public:
	Mushroom(eq::BitmapTexture mushroomTexture, eq::Math::Vector2 position);

	eq::Sprite getSprite() { return mushroomSprite; }
};