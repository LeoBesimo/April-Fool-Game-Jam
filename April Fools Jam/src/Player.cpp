#include "Player.hpp"

Player::Player(eq::Math::Vector2 position) 
{
	m_Collider = new eq::Physics::BoxShape(position, 0, eq::Physics::Materials::DEFAULT, eq::Math::Vector2(20, 40));
	if (m_SpriteSheet.read("assets/wizzard_m_run_anim_f0.bmp"))
		OutputDebugString(L"Loaded Spritesheet\n");
	
	m_SpriteSheet.invertY();

	m_AnimationFrame = eq::Sprite(m_SpriteSheet);
	m_AnimationFrame.scale(4, 4);
	//m_AnimationFrame.preprocessSprite();
	m_AnimationFrame.setCameraDependent(true);
	//m_AnimationFrame.setPosition(eq::Math::Vector2(100, 100));
}

void Player::update()
{
	m_AnimationFrame.setPosition(
		eq::Math::Vector2(m_Collider->getPosition().x-m_AnimationFrame.getSize().x,
			m_Collider->getPosition().y - m_AnimationFrame.getScaledSize().y));
}
