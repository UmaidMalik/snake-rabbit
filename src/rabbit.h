#pragma once

#ifndef RABBIT_H
#define RABBIT_H

#include "raylib.h"
#include "snake.h"

typedef struct
{
    Vector2 position;
    Texture texture;
} Rabbit;

void Rabbit_Init(Rabbit* rabbit);
void Rabbit_BindTexture(Rabbit* rabbit, Texture texture);
void Rabbit_Render(Rabbit* rabbit);
void Rabbit_ResetLocation(Rabbit* rabbit, Snake* snake);
void Rabbit_Move(Rabbit* rabbit, Snake* snake);

#endif