#include "Floor.hpp"

Floor::Floor(eq::BitmapTexture& grass, eq::BitmapTexture& grassGold, eq::BitmapTexture& dirt, eq::BitmapTexture& dirtGold, eq::Math::Vector2 position, float height):
	eq::Physics::BoxShape(position, 0, eq::Physics::Material(0, 0, 1, 1), eq::Math::Matrix2x2(16, 0, 0, 32))

{
	eq::BitmapTexture goldenFloor(32,height);
	eq::BitmapTexture normalFloor(32,height);

	eq::Sprite tempGoldDirt(dirtGold);
	eq::Sprite tempDirt(dirt);
	eq::Sprite tempGoldGrass(grassGold);
	eq::Sprite tempGrass(grass);

	tempGoldDirt.scale(2, 2);
	tempDirt.scale(2, 2);
	tempGoldGrass.scale(2, 2);
	tempGrass.scale(2, 2);

	tempGoldDirt.preprocessSprite();
	tempDirt.preprocessSprite();
	tempGoldGrass.preprocessSprite();
	tempGrass.preprocessSprite();

	goldenFloor.drawSprite(tempGoldGrass);
	normalFloor.drawSprite(tempGrass);

	for (unsigned int i = tempGoldDirt.getScaledSize().y; i < height; i += tempGoldDirt.getScaledSize().y)
	{
		goldenFloor.drawSprite(tempGoldDirt,0,i);
		normalFloor.drawSprite(tempDirt,0,i);
	}

	normal = eq::Sprite(normalFloor);
	gold = eq::Sprite(goldenFloor);

	normal.setPosition(position + eq::Math::Vector2(-16, 32));
	gold.setPosition(position + eq::Math::Vector2(-16, 32));

	normal.preprocessSprite();
	gold.preprocessSprite();
}
