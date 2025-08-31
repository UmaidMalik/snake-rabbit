/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "position.h"
#include "snake.h"
#include "food.h"
#include "game.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

void AddToTextureArray(Texture tex);
bool HasSnakeTouchFood(Snake* snake, Food* food);
Texture texture_array[10];
int texture_array_size = 0;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + 32, "Snake");
	SetTargetFPS(FPS);

	Snake* snake = malloc(sizeof(Snake));
	if (!snake)
	{
		TraceLog(LOG_ERROR, "Snake struct not allocated: out of memory");
		exit(EXIT_FAILURE);
	}
	InitSnake(snake);
	Food food;
	InitFood(&food);

	int grid_size = GRID_HEIGHT * GRID_WIDTH;
	int grid[grid_size];
	TraceLog(LOG_INFO, "THIS IS THE GRID[0]=%d" , grid[0]);
	Position p = CalculatePosition(13);
	TraceLog(LOG_INFO, "x:%d, y:%d", p.x, p.y);
	int idx = CalculateIndex(&p);
	TraceLog(LOG_INFO, "idx:%d", idx);
	
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture food_tex = LoadTexture("wabbit_16x16.png");
	AddToTextureArray(food_tex);
	BindFoodTexture(&food ,food_tex);
	Texture snake_tex = LoadTexture("snake_body_16x16.png");
	BindSnakeTexture(snake, snake_tex);
	AddToTextureArray(snake_tex);
	
	float interval = 0.150f; // 0.150f , 0.050f
	float speed = 10.0f;
	float dt = 0.0f;
	int random_idx = 0;
	float time_accummulated = 0.0f;
	
	// random_idx = GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1);

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		if (HasSnakeCollided(snake))
		{
			break;
		}
		dt = GetFrameTime();
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
		if (IsKeyPressed(KEY_SPACE))
		{
			snake->length += 1;
		}

		double current_time = GetTime();

		time_accummulated += dt;

		for (int i = 0; i < grid_size; i++) {

		}

		if (time_accummulated >= interval) {
			
			// update logic frequency
			MoveSnake(snake);
			if (HasSnakeTouchFood(snake, &food))
			{
				SnakeEatsFood(snake);
				ResetLocation(&food);
			}
			time_accummulated = 0.0f;
		}

		BeginDrawing();

		ClearBackground(SKYBLUE);
		
		
		RenderSnake(snake);
		RenderFood(&food);
		
		for (int i = 0; i < GRID_WIDTH; i++)

		DrawRectangle(0, SCREEN_HEIGHT, SCREEN_WIDTH, 32, DARKBLUE);
		DrawText("Hello Raylib", SCREEN_WIDTH / 2, 0, 50, MAGENTA);
		DrawCircle(GetMouseX(), GetMouseY(), 10, RED);
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

Position CalculatePosition(int idx)
{
	int px = idx % GRID_WIDTH;
	int py = idx / GRID_WIDTH;
	Position p = {px, py};
	return p;
}

int CalculateIndex(Position* p)
{
	int idx = 0;
	idx = p->x + (GRID_WIDTH * p->y);
	return idx;
}

void Render()
{

}

void AddToTextureArray(Texture tex)
{
	texture_array[texture_array_size++] = tex;
}

bool HasSnakeTouchFood(Snake* snake, Food* food)
{
	if (snake->body[0].x == food->position.x && snake->body[0].y == food->position.y)
	{
		return true;
	}
	return false;
}

void GameLogic()
{

}


