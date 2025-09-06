#pragma once

#ifndef GAME_H
#define GAME_H

#define GAME_SCORE (game->snake->length - INIT_SNAKE_SIZE)

#include "raylib.h"
#include "game_buffers.h"
#include "game_state.h"
#include "timer.h"
#include "rabbit.h"
#include "shader_handle.h"
#include "window_setting.h"

struct Snake;

typedef struct Game
{
	GameBuffers* buffers;
	GameState game_state;
	struct Snake* snake;
	Rabbit* rabbit;
	Rabbit* wabbit;
	Timer* timer;
	ShaderHandle* shader_handle;
    WindowSetting* window_setting;
} Game;

Vector2 Game_CalculatePosition(Game* game, int idx);
int Game_CalculateIndex(Game* game, Vector2* p);

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