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
#include "game.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir


Position CalculatePosition(int idx);
int CalculateIndex(Position* p);
void Render(void);

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
	SetTargetFPS(FPS);

	Snake snake2 = InitSnake2();
	Snake *snake2_ptr = &snake2;
	Snake* snake = malloc(sizeof(Snake));
	if (!snake)
	{
		TraceLog(LOG_ERROR, "out of memory");
		exit(EXIT_FAILURE);
	}
	InitSnake(snake);
	snake2.body->x;
	

	int grid_size = GRID_HEIGHT * GRID_WIDTH;
	//int grid[grid_size] = [];
	Position p = CalculatePosition(13);
	TraceLog(LOG_INFO, "x:%d, y:%d", p.x, p.y);
	int idx = CalculateIndex(&p);
	TraceLog(LOG_INFO, "idx:%d", idx);
	
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture snake_tex = LoadTexture("snake_body_16x16.png");
	
	float interval = 0.20f;
	float speed = 10.0f;
	float dt = 0.0f;
	int random_idx = 0;
	float time_accummulated = 0.0f;
	
	// random_idx = GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1);

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		dt = GetFrameTime();
		
		double current_time = GetTime();

		time_accummulated += dt;

		if (time_accummulated >= interval) {
			
			
			time_accummulated = 0.0f;
		}


		BeginDrawing();

		ClearBackground(SKYBLUE);
		
		DrawTexture(wabbit, 400, 200, WHITE);
		DrawTexture(snake_tex, 400, 300, WHITE);
		for (int i = 0; i < GRID_WIDTH; i++)
		{
			for (int j = 0; j < GRID_HEIGHT; j++)
			{
				if (i == GRID_WIDTH - 1 || i == 0 || j == GRID_HEIGHT - 1 || j == 0)
				{
					DrawTexture(snake_tex, TILE_SIZE * i, j * TILE_SIZE, PURPLE);
				}
			}
		}
		DrawText("Hello Raylib", SCREEN_WIDTH / 2, 0, 50, MAGENTA);
		
		Position _p = CalculatePosition(random_idx);
		DrawTexture(snake_tex, _p.x * TILE_SIZE, _p.y * TILE_SIZE, WHITE);
		DrawCircle(GetMouseX(), GetMouseY(), 10, RED);
		EndDrawing();



	}

	// cleanup
	UnloadTexture(wabbit);
	UnloadTexture(snake_tex);

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

void Render() {

}

