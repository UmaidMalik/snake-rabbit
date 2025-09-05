#pragma once

#ifndef GAME_BUFFERS_H
#define GAME_BUFFERS_H

typedef struct
{
    char score[32];
    char fps[32];
    char high_score[32];
} GameBuffers;

void GameBuffer_UpdateScore(GameBuffers* buffers, int score);
void GameBuffer_UpdateFPS(GameBuffers* buffers, int fps);
void GameBuffer_UpdateHighScore(GameBuffers* buffers, int high_score);

#endif