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
#define GAME_SCORE (game->snake->length - INIT_SNAKE_SIZE)

#define SCREEN_WIDTH (GRID_WIDTH * TILE_SIZE)
#define SCREEN_HEIGHT (GRID_HEIGHT * TILE_SIZE)

#include "raylib.h"
#include "game_buffers.h"
#include "game_state.h"
#include "timer.h"
#include "rabbit.h"
#include "shader_handle.h"

struct Snake;

typedef struct
{
	GameBuffers* buffers;
	GameState game_state;
	struct Snake* snake;
	Rabbit* rabbit;
	Rabbit* wabbit;
	Timer* timer;
	ShaderHandle* shader_handle;
} Game;

Vector2 Game_CalculatePosition(int idx);
int Game_CalculateIndex(Vector2* p);

void Game_GameLogic(Game* game);
void Game_GameRender(Game* game);
void Game_MenuLogic(Game* game);
void Game_MenuRender(Game* game);

bool Game_HasSnakeTouchRabbit(Game* game);

void LoadMenu(Game* game);
void LoadGame(Game* game);

void DrawBottomUI(Game* game);
void DrawShader(Game* game);

#endif