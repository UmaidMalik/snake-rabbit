#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "raylib.h"
#include "position.h"
#include "direction.h"
#include "game.h"

#define INIT_SNAKE_SIZE 3

typedef struct
{
    Vector2 body[GRID_WIDTH * GRID_HEIGHT];
    int length;
    Direction dir;
    Texture texture;
} Snake;

void MoveSnake(Snake* snake);
void SetSnakeDirection(Snake* snake, Direction _dir);
bool HasSnakeCollided(Snake* snake);
void SnakeEatsFood(Snake* snake);
void RenderSnake(Snake* snake);
void BindSnakeTexture(Snake* snake, Texture texture);
void InitSnake(Snake* snake);

#endif