#pragma once

#include "Equinox/Equinox.hpp"

class Floor :
	public eq::Physics::BoxShape
{
private:
	eq::Sprite normal;
	eq::Sprite gold;

	bool isGolden;

public:
	Floor(eq::BitmapTexture& grass, eq::BitmapTexture& grassGold, eq::BitmapTexture& dirt, eq::BitmapTexture& dirtGold, eq::Math::Vector2 position, float height);

	void setGolden(bool golden);

	eq::Sprite getSprite() { return isGolden ? gold : normal; }
};