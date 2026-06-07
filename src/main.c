#include <stdlib.h>
#include "raylib.h"
#include <stdio.h>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include <math.h>

#include <string.h>
#include "snake.h"
#include "rabbit.h"
#include "game.h"
#include "timer.h"
#include "game_buffers.h"
#include "resource_dir.h"
#include "game_state.h"
#include "shader_handle.h"
#include "window_setting.h"

static void Setup(void);
static void UpdateFrame(void);
static void Cleanup(void);
static void LoadResources(void);

static Timer timer;
static GameBuffers buffers;
static Rabbit rabbit;
static Rabbit wabbit;
static Snake snake;
static Game game;
static WindowSetting window_setting;
static ShaderHandle shader_handle;

int main (void)
{
	Setup();
#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateFrame, 0, 1);
#else
	while (!WindowShouldClose())
	{
		UpdateFrame();
	}
	
	Cleanup();
#endif

	return 0;
}

static void Setup()
{
	game.window_setting = &window_setting;
	game.timer = &timer;
	game.buffers = &buffers;
	game.snake = &snake;
	game.rabbit = &rabbit;
	game.wabbit = &wabbit;
	game.shader_handle = &shader_handle;
	game.is_paused = false;

	WindowSetting_Init(game.window_setting);

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	
	InitWindow
	(
		game.window_setting->screen_width, 
		game.window_setting->screen_height + game.window_setting->bottom_ui_height,
		game.window_setting->title
	);

#if !defined(PLATFORM_WEB)
	SearchAndSetResourceDir("resources");
#endif
	SetTargetFPS(game.window_setting->fps);


	const int grid_width = game.window_setting->grid_width;
	const int grid_height = game.window_setting->grid_height;
	const size_t body_capacity = (size_t)grid_width * (size_t)grid_height;

	game.snake->body = malloc(sizeof(Vector2) * body_capacity);

	if (game.snake->body == NULL)
	{
		TraceLog(LOG_ERROR, "Failed to allocate memory for snake body");
		CloseWindow();
		exit(EXIT_FAILURE);
	}

	Snake_Init(&game);
	Rabbit_Init(&game);
	LoadResources();

	game.timer->interval =  0.150f;
	game.timer->rabbit_interval = 0.3f; // 0.15-veryhard 0.3-hard 0.6-medium 1.6-easy
	game.timer->interval_scale = 1.0f;

	game.game_state = MENU;

}

static void LoadResources(void)
{
	#if defined(PLATFORM_WEB)
		const char *resource_prefix = "resources/";
	#else
		const char *resource_prefix = "";
	#endif

	game.shader_handle->target =
		LoadRenderTexture
		(
			window_setting.screen_width, 
			window_setting.screen_height
		);

#if defined(PLATFORM_WEB)
    const char *shader_name = "crt_shader_web.fs";
#else
    const char *shader_name = "crt_shader.fs";
#endif

	game.shader_handle->crt_shader =
		LoadShader
		(
			NULL,
			TextFormat("%s%s", resource_prefix, shader_name)
		);

	game.shader_handle->time_loc =
		GetShaderLocation
		(
			game.shader_handle->crt_shader,
			"uTime"
		);

	Texture2D wabbit_tex = LoadTexture(TextFormat("%swabbit_256x256.png", resource_prefix));
	Texture2D rabbit_tex = LoadTexture(TextFormat("%swabbit_32x32.png", resource_prefix));
	Texture2D snake_tex = LoadTexture(TextFormat("%ssnake_body_32x32.png", resource_prefix));
	
	Rabbit_BindTexture(game.wabbit, wabbit_tex);
	Rabbit_BindTexture(game.rabbit, rabbit_tex);
	Snake_BindTexture(game.snake, snake_tex);
}

static void UpdateFrame(void)
{
	switch(game.game_state)
	{
		case MENU:
		LoadMenu(&game);
		break;
		
		case GAME:
		LoadGame(&game);
		break;
		
		default:
			TraceLog
			(
				LOG_WARNING, 
				"Unknown game state: %d", 
				game.game_state
			);
		break;
	}
}

static void Cleanup()
{
	free(game.snake->body);
	game.snake->body = NULL;

	UnloadTexture(game.rabbit->texture);
	UnloadTexture(game.snake->texture);
	UnloadTexture(game.wabbit->texture);

	UnloadShader(game.shader_handle->crt_shader);
	UnloadRenderTexture(game.shader_handle->target);

	CloseWindow();
}