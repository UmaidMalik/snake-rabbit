#include "food.h"
#include "game.h"

void InitFood(Food* food)
{
    food->position = CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
}

void BindFoodTexture(Food* food, Texture texture)
{
    food->texture = texture;
}

void RenderFood(Food* food)
{
    DrawTexture(food->texture, TILE_SIZE * food->position.x, TILE_SIZE * food->position.y, WHITE);
}

void ResetLocation(Food* food)
{
    food->position = CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
}