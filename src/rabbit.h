#pragma once

typedef struct Game Game;

#include "raylib.h"

typedef struct Rabbit
{
    Vector2 position;
    Texture texture;
} Rabbit;

void Rabbit_Init(Game* game);
void Rabbit_BindTexture(Rabbit* rabbit, Texture texture);
void Rabbit_Render(Game* game);
void Rabbit_ResetLocation(Game* game);
void Rabbit_Move(Game* game);
