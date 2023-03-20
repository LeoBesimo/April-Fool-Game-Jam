#include "Player.hpp"

Player::Player(eq::Math::Vector2 position) 
{
	m_Collider = new eq::Physics::BoxShape(position, 0, eq::Physics::Materials::DEFAULT, eq::Math::Vector2(20, 40));
}
