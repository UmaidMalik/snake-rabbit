#pragma once

#ifndef RABBIT_H
#define RABBIT_H

#include "raylib.h"
#include "snake.h"
#include "game.h"

typedef struct
{
    Vector2 position;
    Texture texture;
} Rabbit;

void RabbitInit(Rabbit* rabbit);
void RabbitBindTexture(Rabbit* rabbit, Texture texture);
void RabbitRender(Rabbit* rabbit);
void RabbitResetLocation(Rabbit* rabbit, Snake* snake);
void RabbitMove(Rabbit* rabbit, Snake* snake);

#endif