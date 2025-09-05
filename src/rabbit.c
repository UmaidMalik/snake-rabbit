#include "rabbit.h"
#include "game_math.h"
#include "game.h"
#include "snake.h"
#include "raylib.h"

void Rabbit_Init(Rabbit* rabbit)
{
    rabbit->position = Game_CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
}

void Rabbit_BindTexture(Rabbit* rabbit, Texture texture)
{
    rabbit->texture = texture;
}

void Rabbit_Render(Rabbit* rabbit)
{
    DrawTexture(rabbit->texture, TILE_SIZE * rabbit->position.x, TILE_SIZE * rabbit->position.y, WHITE);
}

void Rabbit_ResetLocation(Rabbit* rabbit, Snake* snake)
{
    int max_tries = 10000;
    bool flag = true;
    int count = 0;
    while (flag && count < max_tries)
    {
        flag = false;
        rabbit->position = Game_CalculatePosition(GetRandomValue(0, (GRID_WIDTH * GRID_HEIGHT) - 1));
        for (int i = 0; i < snake->length; i++)
        {
            if (rabbit->position.x == snake->body[i].x && rabbit->position.y == snake->body[i].y)
            {
                flag = true;
                break;
            }   
        }
        count++;
    }
}

void Rabbit_Move(Rabbit* rabbit,  Snake* snake)
{
    int max_tries = 50;
    bool flag = true;
    int count = 0;
    while (flag && count < max_tries)
    {
        int dx = GetRandomValue(-1, 1);
        int dy = GetRandomValue(-1, 1);
        flag = false;
        rabbit->position.x = GameMath_Mod((int) (rabbit->position.x + dx), GRID_WIDTH);
        rabbit->position.y = GameMath_Mod((int) (rabbit->position.y + dy), GRID_HEIGHT);
        for (int i = 0; i < snake->length; i++)
        {
            if (rabbit->position.x == snake->body[i].x && rabbit->position.y == snake->body[i].y)
            {
                flag = true;
                break;
            }
        }
        count++;
    }
}