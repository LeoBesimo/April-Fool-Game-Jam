#include "Cloud.hpp"
#include "../Player.hpp"

class Player;

Cloud::Cloud(eq::BitmapTexture cloudTexture, eq::Math::Vector2 position):
	eq::Physics::BoxShape(position,0,eq::Physics::Material(0,0,0,0),eq::Math::Matrix2x2(16,0,0,7.5))
{

	cloud = eq::Sprite(cloudTexture);
	cloud.setPosition(position + eq::Math::Vector2(-16, 7.5));
	cloud.preprocessSprite();

	setTrigger(true);
	setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self)
		{			
			eq::Physics::Shape* other = m.bodyA;
			if (m.bodyA == self)
				other = m.bodyB;

			if (!giveJump)
			{
				//OutputDebugString(L"no yeet\n");
				return;
			}

			if (other->getTag().tagId == 1)
			{
				//OutputDebugString(L"Yeet\n");

				Player* player = static_cast<Player*>(other);
				player->setJumps(1);
				giveJump = false;
			}
		});

	setTag(eq::Physics::Tag(2, L"Cloud"));
}

void Cloud::update(float delta)
{
	if (!isColliding()) giveJump = true;
	BoxShape::update(delta);
}
