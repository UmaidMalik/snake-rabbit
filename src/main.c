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
#include "window_setting.h"

void Setup();
void Loop();
void Cleanup();

static Timer timer;
static GameBuffers buffers;
static Rabbit rabbit;
static Rabbit wabbit;
static Snake snake;
static Game game;
static Game* game_ptr;
static WindowSetting window_setting;

int main ()
{
	game.window_setting = &window_setting;
	WindowSetting_Init(game.window_setting);
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(window_setting.screen_width, 
		window_setting.screen_height + window_setting.bottom_ui_height,
		window_setting.title);
	SearchAndSetResourceDir("resources");
	SetTargetFPS(game.window_setting->fps);

	game.timer = &timer;
	game.buffers = &buffers;
	game.snake = &snake;

	int grid_width = game.window_setting->grid_width;
	int grid_height = game.window_setting->grid_height;
	game.snake->body = malloc(sizeof(Vector2) * grid_width * grid_height);

	game.rabbit = &rabbit;
	game.wabbit = &wabbit;
	Snake_Init(&game);
	Rabbit_Init(&game);

	ShaderHandle shader_handle;
	game.shader_handle = &shader_handle;

	game.shader_handle->target =
		LoadRenderTexture
		(
			window_setting.screen_width, 
			window_setting.screen_height
		);

	game.shader_handle->crt_shader =
		LoadShader(0, "crt_shader.fs");

	game.shader_handle->time_loc =
		GetShaderLocation
		(
			game.shader_handle->crt_shader, "uTime"
		);

	Texture wabbit_tex = LoadTexture("wabbit_256x256.png");
	Rabbit_BindTexture(game.wabbit, wabbit_tex);

	Texture rabbit_tex = LoadTexture("wabbit_32x32.png");
	Rabbit_BindTexture(game.rabbit, rabbit_tex);

	Texture snake_tex = LoadTexture("snake_body_32x32.png");
	Snake_BindTexture(game.snake, snake_tex);
	
	game.timer->interval =  0.150f;
	game.timer->rabbit_interval = 0.3f; // 0.15 very hard 0.3 hard 0.600f medium 1.600f easy
	game.timer->interval_scale = 1.0f;

	game.game_state = MENU;

	Loop();

	Cleanup();
	return 0;
}

void Setup()
{

}

void Loop()
{
	while (!WindowShouldClose())
	{
		switch(game.game_state)
		{
			case MENU:
			LoadMenu(&game);
			break;
			case GAME:
			LoadGame(&game);
			break;
		}
	}
}

void Cleanup()
{
	free(game.snake->body);
	game.snake->body = NULL;
	UnloadTexture(game.rabbit->texture);
	UnloadTexture(game.snake->texture);
	CloseWindow();
}