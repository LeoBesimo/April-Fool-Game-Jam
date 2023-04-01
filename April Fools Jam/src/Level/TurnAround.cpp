#include "TurnAround.hpp"

TurnAround::TurnAround(eq::Math::Vector2 position) :
	eq::Physics::BoxShape(position, 0, eq::Physics::Materials::STATIC, eq::Math::Matrix2x2(15, 0, 0, 15))
{
	setTag(eq::Physics::Tag(7, L"ChangeDir"));

	setTrigger(true);
}

void TurnAround::update(float delta)
{
	setTrigger(true);
	BoxShape::update(delta);
}
