#pragma once

#ifndef GAME_H
#define GAME_H

#define GRID_WIDTH 20
#define GRID_HEIGHT 15
#define TILE_SIZE 32
#define FPS 60

#define BOTTOM_UI_HEIGHT 32
#define BOTTOM_UI_Y_OFFSET 8
#define BOTTOM_UI_TEXT_HEIGHT (BOTTOM_UI_Y_OFFSET + SCREEN_HEIGHT)
#define GAME_SCORE (snake->length - INIT_SNAKE_SIZE)

#define SCREEN_WIDTH (GRID_WIDTH * TILE_SIZE)
#define SCREEN_HEIGHT (GRID_HEIGHT * TILE_SIZE)

Vector2 CalculatePosition(int idx);
int CalculateIndex(Vector2* p);
void Render(void);
void GameLogic();

#endif