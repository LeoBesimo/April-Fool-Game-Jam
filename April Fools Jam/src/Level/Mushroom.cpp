#include "Mushroom.hpp"

Mushroom::Mushroom(eq::BitmapTexture mushroomTexture, eq::Math::Vector2 position) :
	eq::Physics::BoxShape(position + eq::Math::Vector2(0, -3), 0, eq::Physics::Material(0, 0, 0.5, 0.5), eq::Math::Matrix2x2(16, 0, 0, 13))
{
	mushroomSprite = eq::Sprite(mushroomTexture);
	mushroomSprite.scale(2, 2);
	mushroomSprite.preprocessSprite();
	mushroomSprite.setPosition(position + eq::Math::Vector2(-16, 10));

	setTrigger(true);

	setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self)
		{
			eq::Physics::Shape* other = m.bodyA;
			if (m.bodyA == self)
				other = m.bodyB;

			if (((int)m.normal.y) == -1 && other->getTag().tagName == L"Player" && other->getVelocity().y < 20)
			{
				other->setVelocity(eq::Math::Vector2(other->getVelocity().x, 450));
			}
		});
}
