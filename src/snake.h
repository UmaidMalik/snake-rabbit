#pragma once

#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "raylib.h"
#include "direction.h"
#include "game.h"

#define INIT_SNAKE_SIZE 3

typedef struct Snake
{
    Vector2 body[GRID_WIDTH * GRID_HEIGHT];
    int length;
    Direction dir;
    Texture texture;
} Snake;

void Snake_Move(Snake* snake);
void Snake_SetDirection(Snake* snake, Direction _dir);
bool Snake_HasCollided(Snake* snake);
void Snake_EatsRabbit(Snake* snake);
void Snake_Render(Snake* snake);
void Snake_BindTexture(Snake* snake, Texture texture);
void Snake_Init(Snake* snake);

#endif