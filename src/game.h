#ifndef GAME_H
#define GAME_H

#define GRID_WIDTH 80
#define GRID_HEIGHT 45
#define TILE_SIZE 16
#define FPS 60
// 1280
#define SCREEN_WIDTH (GRID_WIDTH * TILE_SIZE)
// 720
#define SCREEN_HEIGHT (GRID_HEIGHT * TILE_SIZE)


Position CalculatePosition(int idx);
int CalculateIndex(Position* p);
void Render(void);
void GameLogic();

#endif