#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include "snake.h"
#include "game.h"

typedef struct
{
    Vector2 position;
    Texture texture;
} Food;

void FoodInit(Food* food);
void FoodBindTexture(Food* food, Texture texture);
void FoodRender(Food* food);
void FoodResetLocation(Food* food, Snake* snake);
void FoodMove(Food* food, Snake* snake);

#endif