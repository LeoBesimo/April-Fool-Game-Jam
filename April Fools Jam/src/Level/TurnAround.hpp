#pragma once

#include "Equinox/Equinox.hpp"

class TurnAround:
	public eq::Physics::BoxShape
{
private:
	bool enableTimer = true;

public:
	TurnAround(eq::Math::Vector2 position);
	void update(float delta);
};