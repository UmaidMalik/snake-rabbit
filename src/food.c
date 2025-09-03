#include "food.h"
#include "game_math.h"

void FoodInit(Food* food)
{
    food->position = CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
}

void FoodBindTexture(Food* food, Texture texture)
{
    food->texture = texture;
}

void FoodRender(Food* food)
{
    DrawTexture(food->texture, TILE_SIZE * food->position.x, TILE_SIZE * food->position.y, WHITE);
}

void FoodResetLocation(Food* food, Snake* snake)
{
    int max_tries = 10000;
    bool flag = true;
    int count = 0;
    while (flag && count < max_tries)
    {
        flag = false;
        food->position = CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
        for (int i = 0; i < snake->length; i++)
        {
            if (food->position.x == snake->body[i].x && food->position.y == snake->body[i].y)
            {
                flag = true;
                break;
            }   
        }
        count++;
    }
}

void FoodMove(Food* food,  Snake* snake)
{
    int max_tries = 50;
    bool flag = true;
    int count = 0;
    while (flag && count < max_tries)
    {
        int dx = GetRandomValue(-1, 1);
        int dy = GetRandomValue(-1, 1);
        flag = false;
        food->position.x = game_math_mod((int) (food->position.x + dx), GRID_WIDTH);
        food->position.y = game_math_mod((int) (food->position.y + dy), GRID_HEIGHT);
        for (int i = 0; i < snake->length; i++)
        {
            if (food->position.x == snake->body[i].x && food->position.y == snake->body[i].y)
            {
                flag = true;
                break;
            }
        }
        count++;
    }
}