#pragma once

#include <Equinox/Equinox.hpp>

#include "Floor.hpp"
#include "Platform.hpp"
#include "Cloud.hpp"
#include "Mushroom.hpp"

class Level
{
private:
	eq::BitmapTexture grass;
	eq::BitmapTexture grassGold;
	eq::BitmapTexture platform;
	eq::BitmapTexture platformGold;
	eq::BitmapTexture dirt;
	eq::BitmapTexture dirtGold;
	eq::BitmapTexture cloud;
	eq::BitmapTexture mushroom;

	std::vector<Floor*> floorTiles;
	std::vector<Platform*> platformTiles;
	std::vector<Cloud*> cloudTiles;
	std::vector<Mushroom*> mushroomTiles;

	eq::Math::Vector2 levelOffset;

	const uint32_t levelWidth = 40;
	const uint32_t levelHeight = 30;

	void loadTextures();
	void generateLevel(eq::Physics::PhysicsWorld& world);


public:

	Level(eq::Physics::PhysicsWorld& world);


	void render();

};