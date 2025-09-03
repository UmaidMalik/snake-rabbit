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
#include "food.h"
#include "game.h"
#include "timer.h"
#include "game_buffers.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "game_state.h"

bool HasSnakeTouchFood(Snake* snake, Food* food);
void GameLogic(Snake* snake, Food* food);
void GameRender(Snake* snake, Food* food, GameBuffers* buffers);
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

RenderTexture2D target;
Snake* snake;
Food food;
Food wabbit;
GameBuffers buffers;
Shader crt_shader;
int time_loc;

Timer timer;
GameState game_state;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + BOTTOM_UI_HEIGHT, "Snake");
	SetTargetFPS(FPS);

	snake = malloc(sizeof(Snake));
	if (!snake)
	{
		TraceLog(LOG_ERROR, "Snake struct not allocated: out of memory");
		exit(EXIT_FAILURE);
	}
	
	InitSnake(snake);
	FoodInit(&food);
	
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	crt_shader = LoadShader(0, "crt_shader.fs");
	time_loc = GetShaderLocation(crt_shader, "uTime");

	Texture wabbit_tex = LoadTexture("wabbit_256x256.png");
	FoodBindTexture(&wabbit, wabbit_tex);

	// Load a texture from the resources directory
	Texture food_tex = LoadTexture("wabbit_32x32.png");
	FoodBindTexture(&food ,food_tex);

	Texture snake_tex = LoadTexture("snake_body_32x32.png");
	BindSnakeTexture(snake, snake_tex);
	
	float interval = 0.150f;
	float rabbit_interval = 0.6f; // 0.600f medium 1.600f easy
	int random_idx = 0;
	timer.interval = interval;
	timer.rabbit_interval = rabbit_interval;
	timer.interval_scale = 1.0f;

	game_state = MENU;

	// game loop
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

	// cleanup
	UnloadTexture(food.texture);
	UnloadTexture(snake->texture);

	free(snake);

	// destroy the window and cleanup the OpenGL context
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

bool HasSnakeTouchFood(Snake* snake, Food* food)
{
	if ((int)snake->body[0].x == (int)food->position.x && (int)snake->body[0].y == (int)food->position.y)
	{
		return true;
	}
	return false;
}

void GameLogic(Snake* snake, Food* food)
{
	timer_update(&timer);
	if (HasSnakeCollided(snake))
	{
		InitSnake(snake);
		game_state = MENU;
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
	// TODO: removed this below  
	// if (IsKeyPressed(KEY_SPACE))
	// {
	// 	snake->length += 1;
	// }

	if (HasSnakeTouchFood(snake, food))
	{
		SnakeEatsFood(snake);
		FoodResetLocation(food, snake);
	}

	TraceLog(LOG_INFO, "SNAKE POS: {%f,%f}", snake->body[0].x, snake->body[0].y);
	TraceLog(LOG_INFO, "FOOD  POS: {%f,%f}", food->position.x, food->position.y);

	if (timer.time_accumulated >= timer.interval * timer.interval_scale)
	{
		MoveSnake(snake);
		timer.time_accumulated = 0.0f;
	}

	if (timer.rabbit_move_time_accum >= timer.rabbit_interval)
	{
		FoodMove(food, snake);
		timer.rabbit_move_time_accum = 0.0f;
	}
	
}

void GameRender(Snake* snake, Food* food, GameBuffers* buffers)
{
	ClearBackground(SKYBLUE);
	RenderSnake(snake);
	FoodRender(food);
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

	GameLogic(snake, &food);
	BeginTextureMode(target);
	ClearBackground(WHITE);
	GameRender(snake, &food, &buffers);
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