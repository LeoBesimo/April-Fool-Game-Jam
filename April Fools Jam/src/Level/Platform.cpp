#include "Platform.hpp"

Platform::Platform(eq::BitmapTexture& platform, eq::BitmapTexture& goldenPlatform, eq::Math::Vector2 position, float width):
	eq::Physics::BoxShape(position, 0, eq::Physics::Material(0,0,1,1), eq::Math::Matrix2x2(width / 2, 0, 0, 4))
{

	eq::BitmapTexture pGoldTemp(width,8);
	eq::BitmapTexture pTemp(width,8);

	eq::Sprite tempP(platform);
	eq::Sprite tempGoldP(goldenPlatform);

	tempP.scale(2, 2);
	tempGoldP.scale(2, 2);
	tempP.preprocessSprite();
	tempGoldP.preprocessSprite();

	for (unsigned int i = 0; i < width; i += tempP.getScaledSize().x)
	{
		pGoldTemp.drawSprite(tempGoldP, i, 0);
		pTemp.drawSprite(tempP, i, 0);
	}

	normal = eq::Sprite(pTemp);
	golden = eq::Sprite(pGoldTemp);

	normal.setPosition(position + eq::Math::Vector2(-width / 2, 4));
	golden.setPosition(position + eq::Math::Vector2(-width / 2, 4));

	normal.preprocessSprite();
	golden.preprocessSprite();

	setTag(eq::Physics::Tag(2, L"Platform"));

	setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self)
		{
			eq::Physics::Shape* other = m.bodyA;
			if (self == m.bodyA)
				other = m.bodyB;
		
			/*if (other->getVelocity().y > 0)
				self->setTrigger(true);
			else
				self->setTrigger(false);*/
			if (((int)m.normal.y) == -1)
				self->setTrigger(false);
			else
				self->setTrigger(true);

			if (other->getTag().tagName == L"Enemy")
			{
				setGolden(true);
			}
		
		});
}

void Platform::setGolden(bool golden)
{
	isGolden = golden;
	if (golden)
		setMaterial(eq::Physics::Material(0, 0, 0.1, 0.1));
	else
		eq::Physics::Material(0, 0, 1, 1);	
}
