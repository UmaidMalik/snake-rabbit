#pragma once

#ifndef RABBIT_H
#define RABBIT_H

#include "raylib.h"

typedef struct Game;

typedef struct
{
    Vector2 position;
    Texture texture;
} Rabbit;

void Rabbit_Init(Game* game);
void Rabbit_BindTexture(Game* game, Texture texture);
void Rabbit_Render(Game* game);
void Rabbit_ResetLocation(Game* game);
void Rabbit_Move(Game* game);

#endif