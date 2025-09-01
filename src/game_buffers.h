#ifndef GAME_BUFFERS_H
#define GAME_BUFFERS_H

typedef struct
{
    char score[32];
    char fps[32];
    char high_score[32];
} GameBuffers;

void GameBufferUpdateScore(GameBuffers* buffers, int score);
void GameBufferUpdateFPS(GameBuffers* buffers, int fps);
void GameBufferUpdateHighScore(GameBuffers* buffers, int high_score);

#endif