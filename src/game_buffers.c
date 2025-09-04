#include <string.h>
#include <stdio.h>
#include "game_buffers.h"

void GameBuffer_UpdateScore(GameBuffers* buffers, int score)
{
    snprintf(buffers->score, sizeof(buffers->score), "SCORE: %d", score);
}

void GameBuffer_UpdateFPS(GameBuffers* buffers, int fps)
{
    snprintf(buffers->fps, sizeof(buffers->fps), "FPS: %d", fps);
}

void GameBuffer_UpdateHighScore(GameBuffers* buffers, int high_score)
{
    snprintf(buffers->high_score, sizeof(buffers->high_score), "HIGH SCORE: %d", high_score);
}