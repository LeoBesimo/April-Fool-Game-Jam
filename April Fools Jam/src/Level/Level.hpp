#pragma once

#include <Equinox/Equinox.hpp>
#include <algorithm>

#include "Floor.hpp"
#include "Platform.hpp"
#include "Cloud.hpp"
#include "Mushroom.hpp"
#include "Level.hpp"
#include "Button.hpp"
#include "Enemy.hpp"
#include "TurnAround.hpp"
#include "../Player.hpp"

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
	eq::BitmapTexture button;

	std::vector<Floor*> floorTiles;
	std::vector<Platform*> platformTiles;
	std::vector<Cloud*> cloudTiles;
	std::vector<Mushroom*> mushroomTiles;
	std::vector<Enemy*> enemies;

	Button* endLevel;

	eq::Math::Vector2 levelOffset;

	uint8_t levelWidth;
	uint8_t levelHeight;

	eq::Math::Vector2 playerStartPos;

	std::vector<std::vector<char>> levelData;

	eq::Physics::PhysicsWorld* physicsWorld;

	void loadTextures();
	void loadLevel(const char* filePath);
	void generateLevel(eq::Physics::PhysicsWorld& world, int& levelIndex);
	void generateEnemies();


public:
	Level(eq::Physics::PhysicsWorld& world, eq::Math::Vector2 offset ,const char* filePath, int& levelIndex);

	void setStartPos(eq::Math::Vector2 pos) { playerStartPos = pos; }
	eq::Math::Vector2 getStartPos() { return playerStartPos; }
	eq::Math::Vector2 getLevelOffset() { return levelOffset; }

	void update();

	void reset();
	void render();

};