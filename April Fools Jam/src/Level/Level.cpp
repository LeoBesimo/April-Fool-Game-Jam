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
	button.read("assets/button.bmp");

	grass.invertY();
	grassGold.invertY();
	dirt.invertY();
	dirtGold.invertY();
	platform.invertY();
	platformGold.invertY();
	cloud.invertY();
	mushroom.invertY();
	button.invertY();
}

void Level::generateLevel(eq::Physics::PhysicsWorld& world, int& levelIndex)
{
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

			default:
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
				/*tilePosition += eq::Math::Vector2(i * 32, -j * 32);

				if (previousTile == 'p')
					platformWidth++;*/
				Platform* p = new Platform(platform, platformGold, levelOffset + eq::Math::Vector2(i * 32, -j * 32), 32);
				world.addBody(p);
				platformTiles.push_back(p);
				//platformWidth = 1;

				break;
			}

			default:
			{
				/*if (previousTile == 'p')
				{
					Platform* p = new Platform(platform, platformGold, levelOffset + tilePosition / platformWidth, platformWidth * 32);
					world.addBody(p);
					platformTiles.push_back(p);
					platformWidth = 1;
					tilePosition = eq::Math::Vector2(0, 0);
				}*/
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
			{
				Mushroom * mush = new Mushroom(mushroom, levelOffset + eq::Math::Vector2(i * 32, -j * 32));
				world.addBody(mush);
				mushroomTiles.push_back(mush);
				break;
			}

			case 'b':
			{
				endLevel = new Button(button, eq::Math::Vector2(i * 32, -j * 32) + levelOffset);
				endLevel->setTrigger(true);
				endLevel->setOnCollisionFunction([&](eq::Physics::Manifold m, eq::Physics::Shape* self) {

					eq::Physics::Shape* other = m.bodyA;
					if (self == m.bodyA)
						other = m.bodyB;

					if (other->getTag().tagName == L"Player")
						levelIndex++;
				});

				world.addBody(endLevel);
				break;
			}

			case 'u':
			{
				TurnAround* turnAround = new TurnAround(levelOffset + eq::Math::Vector2(i*32, - j * 32));
				world.addBody(turnAround);
				break;
			}

			case 's':
			{
				playerStartPos = eq::Math::Vector2(i * 32, -j * 32) + levelOffset;
				break;
			}
			}
		}
	}
}

void Level::loadLevel(const char* filePath)
{
	std::ifstream file(filePath);

	std::string str;

	while (std::getline(file, str))
	{
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
		std::vector<char> line(str.begin(), str.end());
		levelData.push_back(line);
		levelWidth = line.size();
	}

	levelHeight = levelData.size();
	file.close();
}

void Level::generateEnemies()
{
	for (unsigned int i = 0; i < levelWidth; i++)
	{
		for (int j = 0; j < levelHeight; j++)
		{
			switch (levelData[j][i])
			{
			case 'e':
			{
				Enemy* enemy = new Enemy(levelOffset + eq::Math::Vector2(i * 32, -j * 32));
				enemies.push_back(enemy);
				physicsWorld->addBody(enemy);
				break;
			}

			}
		}
	}
}

Level::Level(eq::Physics::PhysicsWorld& world, eq::Math::Vector2 offset, const char* filePath, int& levelCount)
{
	physicsWorld = &world;
	levelOffset = offset;
	loadTextures();
	loadLevel(filePath);
	generateLevel(world, levelCount);
	generateEnemies();
}

void Level::reset()
{
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		eq::Physics::Tag tag = enemies[i]->getTag();
		tag.tagId = 99;
		enemies[i]->setTag(tag);
	}

	enemies.clear();
	physicsWorld->removeBodyByTagID(99);

	for (unsigned int i = 0; i < floorTiles.size(); i++)
		floorTiles[i]->setGolden(false);
	for (unsigned int i = 0; i < platformTiles.size(); i++)
		platformTiles[i]->setGolden(false);

	generateEnemies();

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

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		eq::Renderer::Draw(enemies[i]->getAnimationFrame());
	}

	eq::Renderer::Draw(endLevel->getSprite());
}

void Level::update()
{

	for (int i = enemies.size() - 1; i >= 0; i--)
	{
		if (enemies[i]->getTag().tagId == 99)
		{
			enemies.erase(enemies.begin() + i);
		}
	}

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update();
	}
}
