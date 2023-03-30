#include "Level.hpp"

void Level::loadTextures()
{
	grass.read("assets/grass.bmp");
	grassGold.read("assets/grass_gold.bmp");
	dirt.read("assets/dirt.bmp");
	dirtGold.read("assets/dirt_gold.bmp");
	platform.read("assets/platform.bmp");
	platformGold.read("assets/platform_gold.bmp");
	cloud.read("assets/cloud.bmp");
	mushroom.read("assets/mushroom.bmp");

	grass.invertY();
	grassGold.invertY();
	dirt.invertY();
	dirtGold.invertY();
	platform.invertY();
	platformGold.invertY();
	cloud.invertY();
	mushroom.invertY();
}

void Level::generateLevel(eq::Physics::PhysicsWorld& world)
{
	char levelData[30][40] = {
		{'f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','f','f','#','f','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','f','f','f','f','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','c','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','c','#','#','#','#','p','p','p','p','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','f','p','p','p','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','f','p','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','f','f','f','f','f','f','f','f','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','f','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','#','#','#','#','#','#','#','#','#','#','m','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','f'},
		{'f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f'},
		{'f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f'}
	};

	for (unsigned int i = 0; i < levelWidth; i++)
	{
		int tileHeight = 1;
		char previousTile = '#';
		eq::Math::Vector2 tilePosition(0, 0);
		char tile = levelData[0][i];

		for (int j = 0; j < levelHeight; j++)
		{
			tile = levelData[j][i];

			switch (tile)
			{
			case 'f':
			{
				tilePosition += eq::Math::Vector2(i * 32, -j * 32);

				if (previousTile == 'f')
				{
					tileHeight++;
				}
				break;
			}

			case '#':
			{
				if (previousTile == 'f')
				{
					Floor* floor = new Floor(grass, grassGold, dirt, dirtGold, levelOffset + tilePosition / tileHeight, tileHeight * 32);
					world.addBody(floor);
					floorTiles.push_back(floor);
					tileHeight = 1;
					tilePosition = eq::Math::Vector2(0, 0);
				}
				break;
			}
			}

			previousTile = tile;
		}

		if (tile == 'f')
		{
			Floor* floor = new Floor(grass, grassGold, dirt, dirtGold, levelOffset + tilePosition / tileHeight, tileHeight * 32);
			world.addBody(floor);
			floorTiles.push_back(floor);
			tileHeight = 1;
			tilePosition = eq::Math::Vector2(0, 0);
		}
	}

	for (int j = 0; j < levelHeight; j++)
	{
		char previousTile = '#';
		int platformWidth = 1;
		eq::Math::Vector2 tilePosition(0, 0);

		for (unsigned int i = 0; i < levelWidth; i++)
		{
			char tile = levelData[j][i];

			switch (tile)
			{
			case 'p':
			{
				tilePosition += eq::Math::Vector2(i * 32, -j * 32);

				if (previousTile == 'p')
					platformWidth++;
				break;
			}

			case '#':
			{
				if (previousTile == 'p')
				{
					Platform* p = new Platform(platform, platformGold, levelOffset + tilePosition / platformWidth, platformWidth * 32);
					world.addBody(p);
					platformTiles.push_back(p);
					platformWidth = 1;
					tilePosition = eq::Math::Vector2(0, 0);
				}
				break;
			}
			}

			previousTile = tile;
		}
	}

	for (unsigned int i = 0; i < levelWidth; i++)
	{
		for (int j = 0; j < levelHeight; j++)
		{
			switch (levelData[j][i])
			{
			case 'c':
			{
				Cloud* c = new Cloud(cloud, levelOffset + eq::Math::Vector2(i * 32, -j * 32));
				world.addBody(c);
				cloudTiles.push_back(c);
				break;
			}

			case 'm':
				Mushroom * mush = new Mushroom(mushroom, levelOffset + eq::Math::Vector2(i * 32, -j * 32));
				world.addBody(mush);
				mushroomTiles.push_back(mush);
				break;
			}
		}
	}
}

Level::Level(eq::Physics::PhysicsWorld& world)
{
	levelOffset = eq::Math::Vector2(-32 * 10, 32 * 10);
	loadTextures();
	generateLevel(world);

	/*for (int i = -256; i < 256; i += 32)
	{
		Floor* floor = new Floor(grass, grassGold, dirt, dirtGold, eq::Math::Vector2(i, -64), 128);
		world.addBody(floor);
		floorTiles.push_back(floor);

		if (i < 0)
			floor->setGolden(true);
	}*/

	/*Floor* floor = new Floor(grass, grassGold, dirt, dirtGold, eq::Math::Vector2(256, -32),128+32);
	world.addBody(floor);
	floorTiles.push_back(floor);*/
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

	for (unsigned int i = 0; i < cloudTiles.size(); i++)
	{
		eq::Renderer::Draw(cloudTiles[i]->getSprite());
	}

	for (unsigned int i = 0; i < mushroomTiles.size(); i++)
	{
		eq::Renderer::Draw(mushroomTiles[i]->getSprite());
	}
}
