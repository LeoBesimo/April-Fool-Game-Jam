#include "Player.hpp"

Player::Player(eq::Math::Vector2 position) :
	eq::Physics::BoxShape(position,0,eq::Physics::Material(1,0,0.6,0.3),eq::Math::Matrix2x2(14,0,0,15))
{
	if (m_SpriteSheet.read("assets/wizard_walk.bmp"))
		OutputDebugString(L"Loaded Spritesheet\n");
	
	m_SpriteSheet.invertY();

	m_AnimationRight.push_back(eq::Sprite(m_SpriteSheet, 0, 0, 16, 16));
	m_AnimationRight.push_back(eq::Sprite(m_SpriteSheet, 16, 0, 16, 16));
	m_AnimationRight.push_back(eq::Sprite(m_SpriteSheet, 32, 0, 16, 16));
	m_AnimationRight.push_back(eq::Sprite(m_SpriteSheet, 48, 0, 16, 16));

	m_AnimationLeft.push_back(eq::Sprite(m_SpriteSheet, 0, 0, 16, 16));
	m_AnimationLeft.push_back(eq::Sprite(m_SpriteSheet, 16, 0, 16, 16));
	m_AnimationLeft.push_back(eq::Sprite(m_SpriteSheet, 32, 0, 16, 16));
	m_AnimationLeft.push_back(eq::Sprite(m_SpriteSheet, 48, 0, 16, 16));

	for (unsigned int i = 0; i < m_AnimationRight.size();i++)
	{
		m_AnimationRight[i].setCameraDependent(true);
		m_AnimationRight[i].scale(2, 2);
		m_AnimationRight[i].preprocessSprite();

		m_AnimationLeft[i].setCameraDependent(true);
		m_AnimationLeft[i].scale(2, 2);
		m_AnimationLeft[i].invertX();
		m_AnimationLeft[i].preprocessSprite();
	}
	
	setTag(eq::Physics::Tag(PLAYER_TAG_ID, L"Player"));
}

void Player::update()
{
	animationStep++;
	if(animationStep > 10)
	{
		animationFrame++;
		animationStep = 0;
	}

	if (isColliding())
		onGround = true;
	else
	{ 
		onGround = false;
		jumps = 0;
	}

	int index = animationFrame % m_AnimationRight.size();

	if (std::abs(getVelocity().x) < 1) setVelocity(eq::Math::Vector2(0, getVelocity().y));
	if (getVelocity().x < 0) lastDirectionLeft = true;
	else if (getVelocity().x > 0) lastDirectionLeft = false;

	setVelocity(eq::Math::Vector2(eq::Math::clamp(getVelocity().x, -300, 300), getVelocity().y));

	for (unsigned int i = 0; i < m_AnimationRight.size();i++)
	{
		m_AnimationRight[i].setPosition(eq::Math::Vector2(
			getPosition().x- m_AnimationRight[i].getScaledSize().x/2,
			getPosition().y + m_AnimationRight[i].getScaledSize().y/2)
		);

		m_AnimationLeft[i].setPosition(eq::Math::Vector2(
			getPosition().x - m_AnimationRight[i].getScaledSize().x / 2,
			getPosition().y + m_AnimationRight[i].getScaledSize().y / 2)
		);
	}
}

eq::Sprite Player::getAnimationFrame()
{
	if (lastDirectionLeft)
	{
		return (getVelocity().len() > 1) ? m_AnimationLeft[animationFrame % m_AnimationLeft.size()] : m_AnimationLeft[0];
	}
	else
	{
		return (getVelocity().len() > 1) ? m_AnimationRight[animationFrame % m_AnimationRight.size()] : m_AnimationRight[0];
	}
}
