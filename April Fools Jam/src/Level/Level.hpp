#pragma once

#include <Equinox/Equinox.hpp>

#include "Floor.hpp"
#include "Platform.hpp"

class Level
{
private:
	eq::BitmapTexture grass;
	eq::BitmapTexture grassGold;
	eq::BitmapTexture platform;
	eq::BitmapTexture platformGold;
	eq::BitmapTexture dirt;
	eq::BitmapTexture dirtGold;

	std::vector<Floor*> floorTiles;
	std::vector<Platform*> platformTiles;

	void loadTextures();

public:

	Level(eq::Physics::PhysicsWorld& world);

	void render();

};