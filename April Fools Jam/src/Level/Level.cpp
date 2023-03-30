#include "Level.hpp"

void Level::loadTextures()
{
	grass.read("assets/grass.bmp");
	grassGold.read("assets/grass_gold.bmp");
	dirt.read("assets/dirt.bmp");
	dirtGold.read("assets/dirt_gold.bmp");
	platform.read("assets/platform.bmp");
	platformGold.read("assets/platform_gold.bmp");

	grass.invertY();
	grassGold.invertY();
	dirt.invertY();
	dirtGold.invertY();
	platform.invertY();
	platformGold.invertY();
}

Level::Level(eq::Physics::PhysicsWorld& world)
{
	loadTextures();

	for (int i = -256; i < 256; i += 32)
	{
		Floor* floor = new Floor(grass, grassGold, dirt, dirtGold, eq::Math::Vector2(i, -64), 128);
		world.addBody(floor);
		floorTiles.push_back(floor);

		if (i < 0)
			floor->setGolden(true);
	}
}

void Level::render()
{
	for (unsigned int i = 0; i < floorTiles.size(); i++)
	{
		eq::Renderer::Draw(floorTiles[i]->getSprite());
	}

	for (unsigned int i = 0; i < platformTiles.size(); i++)
	{
		eq::Renderer::Draw(platformTiles[i]->getSprite());
	}
}
