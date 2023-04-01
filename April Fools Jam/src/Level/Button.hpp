#pragma once

#include <Equinox/Equinox.hpp>

class Button :
	public eq::Physics::BoxShape
{

private:

	eq::Sprite sprite;

public:

	Button(eq::BitmapTexture buttonTexture, eq::Math::Vector2 position);
	
	eq::Sprite getSprite() { return sprite; }

};