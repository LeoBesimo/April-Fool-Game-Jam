#include "Button.hpp"

Button::Button(eq::BitmapTexture buttonTexture, eq::Math::Vector2 position):
	eq::Physics::BoxShape(position + eq::Math::Vector2(0,-3), 0, eq::Physics::Material(0, 0, 1, 1), eq::Math::Matrix2x2(12, 0, 0, 13))
{
	sprite = eq::Sprite(buttonTexture);
	sprite.setPosition(position + eq::Math::Vector2(-12, 10));
	sprite.scale(2, 2);
	sprite.preprocessSprite();
}
