#include "Platform.hpp"

//Platform::Platform(eq::Math::Vector2 position, float width) :
//	eq::Physics::BoxShape(position, 0, eq::Physics::Material(0,0,0.4,0.4), eq::Math::Matrix2x2(width / 2, 0, 0, 4))
//{
//	texture.read("assets/Platform.bmp");
//	eq::BitmapTexture temp(width, 16);
//	eq::Sprite tempSprite(texture);
//	tempSprite.scale(2, 2);
//	tempSprite.preprocessSprite();
//
//	for (unsigned int i = 0; i < width; i += tempSprite.getScaledSize().x)
//	{
//		temp.drawSprite(tempSprite, i, 0);
//	}
//
//	setTag(eq::Physics::Tag(0, L"Platform"));
//
//	sprite = eq::Sprite(temp);
//	sprite.setPosition(position + eq::Math::Vector2(-width / 2, getScale().b.y));
//	sprite.preprocessSprite();
//
//	setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self)
//		{
//			eq::Physics::Shape* other = m.bodyA;
//			if (self == m.bodyA)
//				other = m.bodyB;
//
//			if (other->getVelocity().y > 0)
//				self->setTrigger(true);
//			else
//				self->setTrigger(false);
//		});
//}

Platform::Platform(eq::BitmapTexture& platform, eq::BitmapTexture& goldenPlatform, eq::Math::Vector2 position, float width):
	eq::Physics::BoxShape(position, 0, eq::Physics::Material(0,0,1,1), eq::Math::Matrix2x2(width / 2, 0, 0, 4))

{


	setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self)
		{
			eq::Physics::Shape* other = m.bodyA;
			if (self == m.bodyA)
				other = m.bodyB;
		
			if (other->getVelocity().y > 0)
				self->setTrigger(true);
			else
				self->setTrigger(false);
		});

}
