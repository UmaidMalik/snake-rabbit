#pragma once

#ifndef RABBIT_H
#define RABBIT_H

#include "raylib.h"
#include "game.h"

struct Snake;

typedef struct
{
    Vector2 position;
    Texture texture;
} Rabbit;

void Rabbit_Init(Game* game);
void Rabbit_BindTexture(Game* game, Texture texture);
void Rabbit_Render(Game* game);
void Rabbit_ResetLocation(Game* game);
void Rabbit_Move(Rabbit* rabbit, struct Snake* snake);

#endif