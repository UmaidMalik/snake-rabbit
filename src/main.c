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
	game_ptr = &game;
	WindowSetting_Init(window_setting);
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + BOTTOM_UI_HEIGHT, window_setting.title);
	SearchAndSetResourceDir("resources");
	SetTargetFPS(FPS);

	game_ptr->timer = &timer;
	game_ptr->buffers = &buffers;
	game_ptr->snake = &snake;

	game_ptr->rabbit = &rabbit;
	game_ptr->wabbit = &wabbit;
	Snake_Init(game_ptr->snake);
	Rabbit_Init(game_ptr->rabbit);
	
	

	ShaderHandle shader_handle;
	game_ptr->shader_handle = &shader_handle;
	game_ptr->shader_handle->target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	game_ptr->shader_handle->crt_shader = LoadShader(0, "crt_shader.fs");
	game_ptr->shader_handle->time_loc = GetShaderLocation(game_ptr->shader_handle->crt_shader, "uTime");

	Texture wabbit_tex = LoadTexture("wabbit_256x256.png");
	Rabbit_BindTexture(game_ptr->wabbit, wabbit_tex);

	Texture rabbit_tex = LoadTexture("wabbit_32x32.png");
	Rabbit_BindTexture(game_ptr->rabbit, rabbit_tex);

	Texture snake_tex = LoadTexture("snake_body_32x32.png");
	Snake_BindTexture(game_ptr->snake, snake_tex);
	
	game_ptr->timer->interval =  0.150f;
	game_ptr->timer->rabbit_interval = 0.3f; // 0.15 very hard 0.3 hard 0.600f medium 1.600f easy
	game_ptr->timer->interval_scale = 1.0f;

	game_ptr->game_state = MENU;

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
		switch(game_ptr->game_state)
		{
			case MENU:
			LoadMenu(game_ptr);
			break;
			case GAME:
			LoadGame(game_ptr);
			break;
		}
	}
}

void Cleanup()
{
	UnloadTexture(game_ptr->rabbit->texture);
	UnloadTexture(game_ptr->snake->texture);
	CloseWindow();
}