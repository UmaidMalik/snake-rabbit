#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"

typedef struct
{
    Vector2 position;
    Texture texture;
} Food;

void InitFood(Food* food);
void BindFoodTexture(Food* food, Texture texture);
void RenderFood(Food* food);
void ResetLocation(Food* food);

#endif