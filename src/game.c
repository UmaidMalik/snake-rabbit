#include <math.h>
#include "game.h"
#include "raylib.h"
#include "snake.h"
#include "rabbit.h"
#include "shader_handle.h"
#include <stddef.h>

Vector2 Game_CalculatePosition(Game* game, int idx)
{
	int px = idx % game->window_setting->grid_width;
	int py = idx / game->window_setting->grid_width;
	Vector2 p = { (float)px, (float)py };
	return p;
}

int Game_CalculateIndex(Game* game, Vector2* p)
{
	int idx = 0;
	idx = p->x + (game->window_setting->grid_width * p->y);
	return idx;
}

void Game_GameLogic(Game* game)
{
	Timer_Update(game->timer);
	if (Snake_HasCollided(game))
	{
		Snake_Init(game);
		game->game_state = MENU;
		game->timer->interval_scale = 1.0f;
	}

	Game_HandleInput(game);

	if (Game_HasSnakeTouchRabbit(game))
	{
		Snake_EatsRabbit(game);
		Rabbit_ResetLocation(game);
	}

	TraceLog(LOG_DEBUG, "SNAKE   POS: {%f,%f}", game->snake->body[0].x, game->snake->body[0].y);
	TraceLog(LOG_DEBUG, "RABBIT  POS: {%f,%f}", game->rabbit->position.x, game->rabbit->position.y);

	if (game->timer->time_accumulated >= game->timer->interval * game->timer->interval_scale)
	{
		Snake_Move(game);
		game->timer->time_accumulated = 0.0f;
	}

	float dx = game->rabbit->position.x - game->snake->body[0].x;
	float dy = game->rabbit->position.y - game->snake->body[0].y;
	dx *= dx;
	dy *= dy;
	float dist = (float)sqrt(dx + dy);

	if (game->timer->rabbit_move_time_accum >= game->timer->rabbit_interval)
	{
		if (dist < 4.0f) {
			Rabbit_Move(game);
			game->timer->rabbit_move_time_accum = 0.0f;
		}
	}
}

void Game_GameRender(Game* game)
{
	ClearBackground(SKYBLUE);
	Snake_Render(game);
	Rabbit_Render(game);
}

void Game_MenuLogic(Game* game)
{
	Vector2 mouse_pos = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
		&& mouse_pos.x >= 32
		&& mouse_pos.x <= 222
		&& mouse_pos.y >= 176
		&& mouse_pos.y <= 230)
	{
		game->game_state = GAME;
	}
}

void Game_MenuRender(Game* game)
{
	ClearBackground(SKYBLUE);
	DrawText("SNAKE", 32, 32, 128, DARKBLUE);
	DrawText("PLAY", 32 + 8, 176, 64, DARKBLUE);
	DrawTexture(game->wabbit->texture, 256, 196, WHITE);
}

bool Game_HasSnakeTouchRabbit(Game* game)
{
	if
	(
		(int)game->snake->body[0].x == (int)game->rabbit->position.x
		&& (int)game->snake->body[0].y == (int)game->rabbit->position.y
	)
	{
		return true;
	}
	return false;
}

void LoadMenu(Game* game)
{
	float time = GetTime();
	SetShaderValue
	(
		game->shader_handle->crt_shader,
		game->shader_handle->time_loc,
		&time,
		SHADER_UNIFORM_FLOAT
	);

	Game_MenuLogic(game);
	BeginTextureMode(game->shader_handle->target);
	ClearBackground(WHITE);
	Game_MenuRender(game);
	EndTextureMode();
	BeginDrawing();
	DrawShader(game);
	EndDrawing();
}

void LoadGame(Game* game)
{
	float time = GetTime();
	SetShaderValue
	(
		game->shader_handle->crt_shader,
		game->shader_handle->time_loc,
		&time,
		SHADER_UNIFORM_FLOAT
	);

	Game_GameLogic(game);
	BeginTextureMode(game->shader_handle->target);
	ClearBackground(WHITE);
	Game_GameRender(game);
	EndTextureMode();

	BeginDrawing();
	DrawShader(game);
	DrawBottomUI(game);
	EndDrawing();
}

void DrawBottomUI(Game* game)
{
	// bottom UI
	DrawRectangle
	(
		0,
		game->window_setting->screen_height,
		game->window_setting->screen_width,
		32,
		DARKBLUE
	);

	// fps render
	GameBuffer_UpdateFPS(game->buffers, GetFPS());
	DrawText
	(
		game->buffers->fps,
		game->window_setting->tile_size,
		game->window_setting->bottom_ui_text_height,
		18,
		WHITE);

	// score render
	GameBuffer_UpdateScore(game->buffers, GAME_SCORE);
	DrawText
	(
		game->buffers->score,
		game->window_setting->tile_size * 4,
		game->window_setting->bottom_ui_text_height,
		18,
		WHITE
	);

	// high score render
	GameBuffer_UpdateHighScore(game->buffers, 0);
	DrawText
	(
		game->buffers->high_score,
		game->window_setting->tile_size * 8,
		game->window_setting->bottom_ui_text_height,
		18,
		WHITE
	);
}

void DrawShader(Game* game)
{
	BeginShaderMode(game->shader_handle->crt_shader);
	DrawTextureRec
	(
	 	game->shader_handle->target.texture,
		(Rectangle)
		{
			0,
			0,
			(float)game->shader_handle->target.texture.width,
			-(float)game->shader_handle->target.texture.height
		},
		(Vector2)
		{
			0, 0
		},
		WHITE
	);
	EndShaderMode();
}

void Game_HandleInput(Game* game)
{
	static const int LEFT_KEYS[] 		= { KEY_A, KEY_LEFT };
	static const int RIGHT_KEYS[] 		= { KEY_D, KEY_RIGHT };
	static const int UP_KEYS[] 			= { KEY_W, KEY_UP };
	static const int DOWN_KEYS[] 		= { KEY_S, KEY_DOWN };
	static const int LEFT_BUTTONS[]		= { GAMEPAD_BUTTON_LEFT_FACE_LEFT };
	static const int RIGHT_BUTTONS[]	= { GAMEPAD_BUTTON_LEFT_FACE_RIGHT};
	static const int UP_BUTTONS[]		= { GAMEPAD_BUTTON_LEFT_FACE_UP};
	static const int DOWN_BUTTONS[]		= { GAMEPAD_BUTTON_LEFT_FACE_DOWN};


	static const int SPEEDUP_KEYS[] 	= { KEY_SPACE };
	static const int SPEEDUP_BUTTONS[] 	= 
	{ 
		GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
		GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
		GAMEPAD_BUTTON_RIGHT_TRIGGER_2
	};
	bool direction_changed = false;
	int gamepad_id = -1;
	for (int i = 0; i < 5; i++)
	{	
		if (IsGamepadAvailable(i))
		{
			gamepad_id = i;
			break;
		}
	}	
	TraceLog(LOG_INFO, "raylib version: %s", RAYLIB_VERSION);

	if (!direction_changed && Game_InputInteract(IsKeyPressed, IsGamepadButtonPressed, LEFT_KEYS, 2, LEFT_BUTTONS, 1, gamepad_id))
	{
		Snake_SetDirection(game, WEST);
		direction_changed = true;
	}
	if (!direction_changed && Game_InputInteract(IsKeyPressed, IsGamepadButtonPressed, RIGHT_KEYS, 2, RIGHT_BUTTONS, 1, gamepad_id))
	{
		Snake_SetDirection(game, EAST);
		direction_changed = true;
	}
	if (!direction_changed && Game_InputInteract(IsKeyPressed, IsGamepadButtonPressed, UP_KEYS, 2, UP_BUTTONS, 1, gamepad_id))
	{
		Snake_SetDirection(game, NORTH);
		direction_changed = true;
	}
	if (!direction_changed && Game_InputInteract(IsKeyPressed, IsGamepadButtonPressed, DOWN_KEYS, 2, DOWN_BUTTONS, 1, gamepad_id))
	{
		Snake_SetDirection(game, SOUTH);
		direction_changed = true;
	}
	if
	(
		Game_InputInteract(IsKeyDown, IsGamepadButtonDown, SPEEDUP_KEYS, 1, SPEEDUP_BUTTONS, 3, gamepad_id)
	)
	{
		game->timer->interval_scale = 0.25f;
	}
	if
	(
		Game_InputInteract(IsKeyReleased, IsGamepadButtonReleased, SPEEDUP_KEYS, 1, SPEEDUP_BUTTONS, 3, gamepad_id)
	)
	{
		game->timer->interval_scale = 1.0f;
	}
	if
	(
		IsKeyPressed(KEY_Q)
		|| IsGamepadButtonPressed(gamepad_id, GAMEPAD_BUTTON_MIDDLE_RIGHT)
	)
	{
		game->game_state = MENU;
		game->timer->interval_scale = 1.0f;
	}
}

bool Game_InputInteract(bool (*IsKeyInteracted)(int), bool (*IsGamepadButtonInteracted)(int, int), const int* keys, int key_count, const int* buttons, int button_count, int gamepad_id)
{
	for (int i = 0; i < key_count; i++)
	{
		if (IsKeyInteracted(keys[i])) return true;
	}
	for (int i = 0; i < button_count; i++)
	{
		if (IsGamepadButtonInteracted(gamepad_id, buttons[i])) return true;
	}
	return false;
}