#pragma once

typedef struct GameBuffers
{
    char score[32];
    char fps[32];
    char high_score[32];
} GameBuffers;

void GameBuffer_UpdateScore(GameBuffers* buffers, int score);
void GameBuffer_UpdateFPS(GameBuffers* buffers, int fps);
void GameBuffer_UpdateHighScore(GameBuffers* buffers, int high_score);