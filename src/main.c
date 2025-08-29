/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <stdio.h>
#include "raylib.h"
#include "position.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#define GRID_WIDTH 80
#define GRID_HEIGHT 45
#define TILE_SIZE 16
static int WIDTH = GRID_WIDTH * TILE_SIZE;
static int HEIGHT = GRID_HEIGHT * TILE_SIZE; 

Position calculate_pos(int idx);
int calculate_index(Position* p);

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(WIDTH, HEIGHT, "Snake");
	
	int grid_size = GRID_HEIGHT * GRID_WIDTH;
	//int grid[grid_size] = [];
	Position p = calculate_pos(13);
	TraceLog(LOG_INFO, "x:%d, y:%d", p.x, p.y);
	int idx = calculate_index(&p);
	TraceLog(LOG_INFO, "idx:%d", idx);
	 

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture snake = LoadTexture("snake_body_16x16.png");
	
	

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		
		if (IsKeyPressed(KEY_F11))
		{
			ToggleBorderlessWindowed();
			if (IsWindowFullscreen())
			{
				SetWindowSize(WIDTH, HEIGHT);
			}
		}

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(SKYBLUE);

		
		

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);

		DrawTexture(snake, 400, 300, WHITE);
		for (int i = 0; i < GRID_WIDTH; i++)
		{
			for (int j = 0; j < GRID_HEIGHT; j++)
			{
				if (i == GRID_WIDTH - 1 || i == 0 || j == GRID_HEIGHT - 1 || j == 0)
				{
					DrawTexture(snake, TILE_SIZE * i, j * TILE_SIZE, PURPLE);
				}
			}
		}

		// draw some text using the default font
		DrawText("Hello Raylib", WIDTH / 2, 0, 50, MAGENTA);
		
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

Position calculate_pos(int idx) {
	int px = idx % GRID_WIDTH;
	int py = idx / GRID_WIDTH;
	Position p = {px, py};
	return p;
}

int calculate_index(Position* p) {
	int idx = 0;
	idx = p->x + (GRID_WIDTH * p->y);
	return idx;
}
