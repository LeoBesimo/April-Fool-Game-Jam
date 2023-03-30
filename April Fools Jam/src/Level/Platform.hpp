#pragma once

#include <Equinox/Equinox.hpp>

class Platform:
	public eq::Physics::BoxShape
{
private:
	eq::Sprite normal;
	eq::Sprite golden;

	bool isGolden;

public:
	Platform(eq::BitmapTexture& platform, eq::BitmapTexture& goldenPlatform, eq::Math::Vector2 position, float width);

	void setGolden(bool golden) { isGolden = golden; }

	eq::Sprite getSprite() { return isGolden ? golden : normal; }
};