/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

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
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "game_state.h"

bool HasSnakeTouchRabbit(Snake* snake, Rabbit* rabbit);
void GameLogic(Snake* snake, Rabbit* rabbit);
void GameRender(Snake* snake, Rabbit* rabbit, GameBuffers* buffers);
void MenuLogic();
void MenuRender();
void GameOverLogic();
void GameOverRender();
void DrawBottomUI(GameBuffers* buffers);
void DrawShader(RenderTexture2D* target, Shader* shader);

void LoadMenu();
void LoadGame();
void LoadGameOver();
void LoadScoreboard();
void Setup();

RenderTexture2D target;
Snake* snake;
Rabbit rabbit;
Rabbit wabbit;
GameBuffers buffers;
Shader crt_shader;
int time_loc;

Timer timer;
GameState game_state;

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + BOTTOM_UI_HEIGHT, "Snake");
	SetTargetFPS(FPS);

	snake = malloc(sizeof(Snake));
	if (!snake)
	{
		TraceLog(LOG_ERROR, "Snake struct not allocated: out of memory");
		exit(EXIT_FAILURE);
	}
	
	InitSnake(snake);
	RabbitInit(&rabbit);
	
	SearchAndSetResourceDir("resources");

	target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	crt_shader = LoadShader(0, "crt_shader.fs");
	time_loc = GetShaderLocation(crt_shader, "uTime");

	Texture wabbit_tex = LoadTexture("wabbit_256x256.png");
	RabbitBindTexture(&wabbit, wabbit_tex);

	// Load a texture from the resources directory
	Texture rabbit_tex = LoadTexture("wabbit_32x32.png");
	RabbitBindTexture(&rabbit , rabbit_tex);

	Texture snake_tex = LoadTexture("snake_body_32x32.png");
	BindSnakeTexture(snake, snake_tex);
	
	int random_idx = 0;
	timer.interval =  0.150f;
	timer.rabbit_interval = 0.3f; // 0.15 very hard 0.3 hard 0.600f medium 1.600f easy
	timer.interval_scale = 1.0f;

	game_state = MENU;

	while (!WindowShouldClose())
	{
		switch(game_state)
		{
			case MENU:
			LoadMenu();
			break;
			case GAME:
			LoadGame();
			break;
		}
	}

	UnloadTexture(rabbit.texture);
	UnloadTexture(snake->texture);
	free(snake);
	CloseWindow();
	return 0;
}

Vector2 CalculatePosition(int idx)
{
    float px = idx % GRID_WIDTH;
	float py = idx / GRID_WIDTH;
	Vector2 p = {px, py};
	return p;
}

int CalculateIndex(Vector2* p)
{
	int idx = 0;
	idx = p->x + (GRID_WIDTH * p->y);
	return idx;
}

bool HasSnakeTouchRabbit(Snake* snake, Rabbit* rabbit)
{
	if ((int)snake->body[0].x == (int)rabbit->position.x && (int)snake->body[0].y == (int)rabbit->position.y)
	{
		return true;
	}
	return false;
}

void GameLogic(Snake* snake, Rabbit* rabbit)
{
	timer_update(&timer);
	if (HasSnakeCollided(snake))
	{
		InitSnake(snake);
		game_state = MENU;
		timer.interval_scale = 1.0f;
	}
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
	{
		SetSnakeDirection(snake, WEST);
	}
	if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
	{
		SetSnakeDirection(snake, EAST);
	}
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
	{
		SetSnakeDirection(snake, NORTH);
	}
	if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
	{
		SetSnakeDirection(snake, SOUTH);
	}
	if (IsKeyDown(KEY_SPACE))
	{
		timer.interval_scale = 0.25f;
	}
	if (IsKeyReleased(KEY_SPACE))
	{
		timer.interval_scale = 1.0f;
	}
	if (IsKeyPressed(KEY_Q))
	{
		game_state = MENU;
		timer.interval_scale = 1.0f;
	}
	// TODO: removed this below  
	// if (IsKeyPressed(KEY_SPACE))
	// {
	// 	snake->length += 1;
	// }

	if (HasSnakeTouchRabbit(snake, rabbit))
	{
		SnakeEatsRabbit(snake);
		RabbitResetLocation(rabbit, snake);
	}

	TraceLog(LOG_DEBUG, "SNAKE   POS: {%f,%f}", snake->body[0].x, snake->body[0].y);
	TraceLog(LOG_DEBUG, "RABBIT  POS: {%f,%f}", rabbit->position.x, rabbit->position.y);

	if (timer.time_accumulated >= timer.interval * timer.interval_scale)
	{
		MoveSnake(snake);
		timer.time_accumulated = 0.0f;
	}

		float dx = rabbit->position.x - snake->body[0].x;
		float dy = rabbit->position.y - snake->body[0].y;
		dx *= dx;
		dy *= dy;
		float dist = (float) sqrt(dx + dy);

	if (timer.rabbit_move_time_accum >= timer.rabbit_interval)
	{
		if (dist < 4.0f) {
		RabbitMove(rabbit, snake);
		timer.rabbit_move_time_accum = 0.0f;
		}
	}
	
}

void GameRender(Snake* snake, Rabbit* rabbit, GameBuffers* buffers)
{
	ClearBackground(SKYBLUE);
	RenderSnake(snake);
	RabbitRender(rabbit);
}

void MenuLogic()
{
	Vector2 mouse_pos = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
	&& mouse_pos.x >= 32 
	&& mouse_pos.x <= 222
	&& mouse_pos.y >= 176
	&& mouse_pos.y <= 230)
	{
		game_state = GAME;
	}
}

void MenuRender()
{
	ClearBackground(SKYBLUE);
	DrawText("SNAKE", 32, 32, 128, DARKBLUE);
	DrawText("PLAY", 32 + 8, 176, 64, DARKBLUE);
	DrawTexture(wabbit.texture, 256, 196, WHITE);
}


void DrawBottomUI(GameBuffers* buffers)
{
	// bottom UI
	DrawRectangle(0, SCREEN_HEIGHT, SCREEN_WIDTH, 32, DARKBLUE);
	// fps render
	GameBufferUpdateFPS(buffers, GetFPS());
	DrawText(buffers->fps, TILE_SIZE, BOTTOM_UI_TEXT_HEIGHT, 18, WHITE);
	// score render
	GameBufferUpdateScore(buffers, GAME_SCORE);
	DrawText(buffers->score, TILE_SIZE * 4, BOTTOM_UI_TEXT_HEIGHT, 18, WHITE);
	// high score render
	GameBufferUpdateHighScore(buffers, 0);
	DrawText(buffers->high_score, TILE_SIZE * 8, BOTTOM_UI_TEXT_HEIGHT, 18, WHITE);
}

void DrawShader(RenderTexture2D* target, Shader* shader)
{
	BeginShaderMode(*shader);
	DrawTextureRec(
		target->texture,
		(Rectangle){ 0, 0, (float)target->texture.width, -(float)target->texture.height },
		(Vector2){ 0, 0 },
		WHITE
	);
	EndShaderMode();
}

void LoadMenu()
{
	float time = GetTime();
	SetShaderValue(crt_shader, time_loc, &time, SHADER_UNIFORM_FLOAT);

	MenuLogic();
	BeginTextureMode(target);
	ClearBackground(WHITE);
	MenuRender();
	EndTextureMode();
	BeginDrawing();
	DrawShader(&target, &crt_shader);
	EndDrawing();
}

void LoadGame()
{
	float time = GetTime();
	SetShaderValue(crt_shader, time_loc, &time, SHADER_UNIFORM_FLOAT);

	GameLogic(snake, &rabbit);
	BeginTextureMode(target);
	ClearBackground(WHITE);
	GameRender(snake, &rabbit, &buffers);
	EndTextureMode();

	BeginDrawing();
	DrawShader(&target, &crt_shader);
	DrawBottomUI(&buffers);
	EndDrawing();
}

void LoadGameOver()
{
	BeginDrawing();
	ClearBackground(SKYBLUE); 
	EndDrawing();
}

void Setup()
{

}