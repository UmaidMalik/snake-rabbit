#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "snake.h"
#include "rabbit.h"
#include "game.h"
#include "timer.h"
#include "game_buffers.h"
#include "resource_dir.h"
#include "game_state.h"
#include "shader_handle.h"

void Setup();

static Timer timer;
static GameBuffers buffers;
static GameState game_state;
static Rabbit rabbit;
static Rabbit wabbit;

int main ()
{
	Game* game = malloc(sizeof(Game));
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + BOTTOM_UI_HEIGHT, "Snake & Rabbit");
	SetTargetFPS(FPS);

	game->timer = &timer;
	game->buffers = &buffers;
	game->game_state = game_state;
	game->snake = malloc(sizeof(Snake));
	if (!game->snake)
	{
		TraceLog(LOG_ERROR, "Snake struct not allocated: out of memory");
		exit(EXIT_FAILURE);
	}
	
	game->rabbit = &rabbit;
	game->wabbit = &wabbit;
	Snake_Init(game->snake);
	Rabbit_Init(game->rabbit);
	
	SearchAndSetResourceDir("resources");

	ShaderHandle shader_handle;
	game->shader_handle = &shader_handle;
	game->shader_handle->target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	game->shader_handle->crt_shader = LoadShader(0, "crt_shader.fs");
	game->shader_handle->time_loc = GetShaderLocation(game->shader_handle->crt_shader, "uTime");

	Texture wabbit_tex = LoadTexture("wabbit_256x256.png");
	Rabbit_BindTexture(game->wabbit, wabbit_tex);

	Texture rabbit_tex = LoadTexture("wabbit_32x32.png");
	Rabbit_BindTexture(game->rabbit, rabbit_tex);

	Texture snake_tex = LoadTexture("snake_body_32x32.png");
	Snake_BindTexture(game->snake, snake_tex);
	
	game->timer->interval =  0.150f;
	game->timer->rabbit_interval = 0.3f; // 0.15 very hard 0.3 hard 0.600f medium 1.600f easy
	game->timer->interval_scale = 1.0f;

	game->game_state = MENU;

	while (!WindowShouldClose())
	{
		switch(game->game_state)
		{
			case MENU:
			LoadMenu(&game);
			break;
			case GAME:
			LoadGame(&game);
			break;
		}
	}

	UnloadTexture(game->rabbit->texture);
	UnloadTexture(game->snake->texture);
	free(game->snake);
	game->snake = NULL;
	free(game);
	game = NULL;
	CloseWindow();
	return 0;
}

void Setup()
{

}