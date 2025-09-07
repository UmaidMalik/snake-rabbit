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
    Vector2* body;
    int length;
    Direction dir;
    Texture texture;
} Snake;

void Snake_Move(Game* game);
void Snake_SetDirection(Game* game, Direction _dir);
bool Snake_HasCollided(Game* game);
void Snake_EatsRabbit(Game* game);
void Snake_Render(Game* game);
void Snake_BindTexture(Snake* snake, Texture texture);
void Snake_Init(Game* game);

#endif