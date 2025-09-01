#include <string.h>
#include <stdio.h>
#include "game_buffers.h"

void GameBufferUpdateScore(GameBuffers* buffers, int score)
{
    snprintf(buffers->score, sizeof(buffers->score), "SCORE: %d", score);
}

void GameBufferUpdateFPS(GameBuffers* buffers, int fps)
{
    snprintf(buffers->fps, sizeof(buffers->fps), "FPS: %d", fps);
}

void GameBufferUpdateHighScore(GameBuffers* buffers, int high_score)
{
    snprintf(buffers->high_score, sizeof(buffers->high_score), "HIGH SCORE: %d", high_score);
}