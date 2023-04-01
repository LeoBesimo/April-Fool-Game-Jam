#include "Enemy.hpp"

Enemy::Enemy(eq::Math::Vector2 position) :
    eq::Physics::BoxShape(position, 0, eq::Physics::Material(1, 0, 0.6, 0.3), eq::Math::Matrix2x2(16,0,0,9))
{
	setGravity(eq::Math::Vector2(0, -250));

	moveForce = eq::Math::Vector2(-1.5 * 10e2,10);

	setInertia(0);

	if (spriteSheet.read("assets/lizard.bmp"))
		OutputDebugString(L"Loaded Spritesheet\n");

	spriteSheet.invertY();

	animationRight.push_back(eq::Sprite(spriteSheet, 0, 0, 16, 16));
	animationRight.push_back(eq::Sprite(spriteSheet, 16, 0, 16, 16));
	animationRight.push_back(eq::Sprite(spriteSheet, 32, 0, 16, 16));
	animationRight.push_back(eq::Sprite(spriteSheet, 48, 0, 16, 16));

	animationLeft.push_back(eq::Sprite(spriteSheet, 0, 0, 16, 16));
	animationLeft.push_back(eq::Sprite(spriteSheet, 16, 0, 16, 16));
	animationLeft.push_back(eq::Sprite(spriteSheet, 32, 0, 16, 16));
	animationLeft.push_back(eq::Sprite(spriteSheet, 48, 0, 16, 16));

	for (unsigned int i = 0; i < animationRight.size(); i++)
	{
		animationRight[i].setCameraDependent(true);
		animationRight[i].scale(2, 2);
		animationRight[i].preprocessSprite();

		animationLeft[i].setCameraDependent(true);
		animationLeft[i].scale(2, 2);
		animationLeft[i].invertX();
		animationLeft[i].preprocessSprite();
	}

	setTag(eq::Physics::Tag(5, L"Enemy"));

	setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self){

		eq::Physics::Shape* other = m.bodyA;
		if (m.bodyA == self)
			other = m.bodyB;


		if (other->getTag().tagName == L"ChangeDir")
		{
			OutputDebugString(L"Trigger\n");

			self->setVelocity(eq::Math::Vector2());
			if(cooldown == 0)
			{
				moveForce *= -1;
				cooldown = 30;
				enableTimer = false;
			}
		}

		else if (other->getTag().tagName == L"Player" && (std::floor(m.normal.y) == -1 || std::floor(m.normal.y) == 1))
		{
			eq::Physics::Tag tag = getTag();
			tag.tagId = 99;
			setTag(tag);
		}

		else
		{
			enableTimer = true;
		}



	});
}

void Enemy::update()
{
	animationStep++;
	if (animationStep > 10)
	{
		animationFrame++;
		animationStep = 0;
	}

	if (cooldown > 0 && enableTimer)
		cooldown--;

	setForce(moveForce * getMass());

	if (getVelocity().x < 0) lastDirectionLeft = true;
	else if (getVelocity().x > 0) lastDirectionLeft = false;

	setVelocity(eq::Math::Vector2(eq::Math::clamp(getVelocity().x, -150, 150), getVelocity().y));

	for (unsigned int i = 0; i < animationRight.size(); i++)
	{
		animationRight[i].setPosition(eq::Math::Vector2(
			getPosition().x - animationRight[i].getScaledSize().x / 2,
			getPosition().y + 7)
		);

		animationLeft[i].setPosition(eq::Math::Vector2(
			getPosition().x - animationRight[i].getScaledSize().x / 2,
			getPosition().y + 7)
		);
	}
}

eq::Sprite Enemy::getAnimationFrame()
{
	if (!lastDirectionLeft)
	{
		return (getVelocity().len() > 1) ? animationLeft[animationFrame % animationLeft.size()] : animationLeft[0];
	}
	else
	{
		return (getVelocity().len() > 1) ? animationRight[animationFrame % animationRight.size()] : animationRight[0];
	}
}
