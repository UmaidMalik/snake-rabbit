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

void AddToTextureArray(Texture tex);
bool HasSnakeTouchFood(Snake* snake, Food* food);
void GameLogic(Snake* snake, Food* food);
void GameRender(Snake* snake, Food* food, GameBuffers* buffers);
void MenuLogic();
void MenuRender();
void GameOverLogic();
void GameOverRender();
void DrawBottomUI(GameBuffers* buffers);
void DrawShader(RenderTexture2D* target, Shader* shader);

Texture texture_array[10];
int texture_array_size = 0;
RenderTexture2D target;
Snake* snake;

Timer timer;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + 32, "Snake");
	SetTargetFPS(FPS);

	snake = malloc(sizeof(Snake));
	if (!snake)
	{
		TraceLog(LOG_ERROR, "Snake struct not allocated: out of memory");
		exit(EXIT_FAILURE);
	}
	GameBuffers buffers;
	InitSnake(snake);
	Food food;
	InitFood(&food);

	int grid_size = GRID_HEIGHT * GRID_WIDTH;
	int grid[grid_size];
	TraceLog(LOG_INFO, "THIS IS THE GRID[0]=%d" , grid[0]);
	Vector2 p = CalculatePosition(13);
	TraceLog(LOG_INFO, "x:%d, y:%d", p.x, p.y);
	int idx = CalculateIndex(&p);
	TraceLog(LOG_INFO, "idx:%d", idx);
	
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
	Shader crt_shader = LoadShader(0, "crt_shader.fs");
	int time_loc = GetShaderLocation(crt_shader, "uTime");

	// Load a texture from the resources directory
	Texture food_tex = LoadTexture("wabbit_16x16.png");
	//AddToTextureArray(food_tex);
	BindFoodTexture(&food ,food_tex);
	Texture snake_tex = LoadTexture("snake_body_16x16.png");
	BindSnakeTexture(snake, snake_tex);
	//AddToTextureArray(snake_tex);
	
	float interval = 0.150f; // 0.150f , 0.050f
	int random_idx = 0;
	timer_set_interval(&timer, interval);

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float time = GetTime();
		SetShaderValue(crt_shader, time_loc, &time, SHADER_UNIFORM_FLOAT);

		GameLogic(snake, &food);
		BeginTextureMode(target);
    	ClearBackground(WHITE);
    	// Draw your game scene here
		GameRender(snake, &food, &buffers);
		EndTextureMode();

		BeginDrawing();
		BeginShaderMode(crt_shader);
		DrawTextureRec(
			target.texture,
			(Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
			(Vector2){ 0, 0 },
			WHITE
		);
		EndShaderMode();
		
		DrawBottomUI(&buffers);

		EndDrawing();

		
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


void AddToTextureArray(Texture tex)
{
	texture_array[texture_array_size++] = tex;
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
		return;
	}
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
	{
		SetSnakeDirection(snake, WEST);
	}
	else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
	{
		SetSnakeDirection(snake, EAST);
	}
	else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
	{
		SetSnakeDirection(snake, NORTH);
	}
	else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
	{
		SetSnakeDirection(snake, SOUTH);
	}
	// TODO: removed this below  
	if (IsKeyPressed(KEY_SPACE))
	{
		snake->length += 1;
	}

	if (HasSnakeTouchFood(snake, food))
	{
		SnakeEatsFood(snake);
		ResetLocation(food);
	}

	if (timer.time_accumulated >= timer.interval) {
		MoveSnake(snake);
		TraceLog(LOG_INFO, "SNAKE POS: {%f,%f}", snake->body[0].x, snake->body[0].y);
		TraceLog(LOG_INFO, "FOOD  POS: {%f,%f}", food->position.x, food->position.y);
		timer.time_accumulated = 0.0f;
	}
}

void GameRender(Snake* snake, Food* food, GameBuffers* buffers)
{
	ClearBackground(SKYBLUE);
	RenderSnake(snake);
	RenderFood(food);
}

void MenuLogic()
{

}

void MenuRender()
{

}

void GameOverLogic()
{

}

void GameOverRender()
{

}

void DrawBottomUI(GameBuffers* buffers)
{
	// bottom ui start
	DrawRectangle(0, SCREEN_HEIGHT, SCREEN_WIDTH, 32, DARKBLUE);
	// fps render
	GameBufferUpdateFPS(buffers, GetFPS());
	DrawText(buffers->fps, TILE_SIZE, SCREEN_HEIGHT + 8, 18, WHITE);
	// end fps render
	// score render
	GameBufferUpdateScore(buffers, snake->length - INIT_SNAKE_SIZE);
	DrawText(buffers->score, TILE_SIZE * 16, SCREEN_HEIGHT + 8, 18, WHITE);
	// end score render
	// bottom ui end
	// high score render
	GameBufferUpdateHighScore(buffers, 0);
	DrawText(buffers->high_score, TILE_SIZE * 32, SCREEN_HEIGHT + 8, 18, WHITE);
	// end high score render
}

void DrawShader(RenderTexture2D* target, Shader* shader)
{

}
