#include "Player.hpp"

Player::Player(eq::Math::Vector2 position) 
{
	if (m_SpriteSheet.read("assets/Wizard_walk.bmp"))
		OutputDebugString(L"Loaded Spritesheet\n");
	
	m_SpriteSheet.invertY();

	m_Animation.push_back(eq::Sprite(m_SpriteSheet, 0, 0, 16, 16));
	m_Animation.push_back(eq::Sprite(m_SpriteSheet, 16, 0, 16, 16));
	m_Animation.push_back(eq::Sprite(m_SpriteSheet, 32, 0, 16, 16));
	m_Animation.push_back(eq::Sprite(m_SpriteSheet, 48, 0, 16, 16));

	for (unsigned int i = 0; i < m_Animation.size();i++)
	{
		m_Animation[i].setCameraDependent(true);
		m_Animation[i].scale(4, 4);
		m_Animation[i].preprocessSprite();
	}

	m_Collider = new eq::Physics::BoxShape(position, 0, eq::Physics::Material(1,0,0,0.6), eq::Math::Matrix2x2(32, 0, 0, 32));

	//m_Collider->setPosition(position);

	m_AnimationFrame = eq::Sprite(m_SpriteSheet,0,0,16,16);
	m_AnimationFrame.scale(2, 2);
	m_AnimationFrame.preprocessSprite();
	m_AnimationFrame.setCameraDependent(true);
	//m_AnimationFrame.setPosition(eq::Math::Vector2(100, 100));
}

void Player::update()
{
	animationStep++;
	if(animationStep > 10)
	{
		animationFrame++;
		animationStep = 0;
	}
	int index = animationFrame % m_Animation.size();

	m_Animation[index].setPosition(
		eq::Math::Vector2(m_Collider->getPosition().x- m_Animation[index].getScaledSize().x/2,
			m_Collider->getPosition().y + m_Animation[index].getScaledSize().y/2));
}
