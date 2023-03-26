#include "Player.hpp"

Player::Player(eq::Math::Vector2 position) 
{
	if (m_SpriteSheet.read("assets/wizzard_m_run_anim_f0.bmp"))
		OutputDebugString(L"Loaded Spritesheet\n");
	
	m_SpriteSheet.invertY();

	m_Collider = new eq::Physics::BoxShape(position, 0, eq::Physics::Material(1,0,0,0.6), eq::Math::Matrix2x2(20, 0, 0, 40));

	//m_Collider->setPosition(position);

	m_AnimationFrame = eq::Sprite(m_SpriteSheet);
	m_AnimationFrame.scale(2, 2);
	//m_AnimationFrame.preprocessSprite();
	m_AnimationFrame.setCameraDependent(true);
	//m_AnimationFrame.setPosition(eq::Math::Vector2(100, 100));
}

void Player::update()
{
	m_AnimationFrame.setPosition(
		eq::Math::Vector2(m_Collider->getPosition().x-m_AnimationFrame.getScaledSize().x/2,
			m_Collider->getPosition().y + m_AnimationFrame.getScaledSize().y/2));
}
