#include "rabbit.h"
#include "game_math.h"
#include "game.h"
#include "snake.h"
#include "raylib.h"

void Rabbit_Init(Game* game)
{
    int grid_width = game->window_setting->grid_width;
    int grid_height = game->window_setting->grid_height;
    game->rabbit->position =
        Game_CalculatePosition
        (
            game,
            GetRandomValue
            (
                0,
                (grid_width * grid_height) - 1
            )
        );
}

void Rabbit_BindTexture(Game* game, Texture texture)
{
    game->rabbit->texture = texture;
}

void Rabbit_Render(Game* game)
{
    int x = game->window_setting->tile_size * game->rabbit->position.x;
    int y = game->window_setting->tile_size * game->rabbit->position.y;
    DrawTexture(game->rabbit->texture, x, y, WHITE);
}

void Rabbit_ResetLocation(Game* game)
{
    Rabbit* rabbit = game->rabbit;
    Snake* snake = game->snake;
    int max_tries = 10000;
    bool flag = true;
    int count = 0;
    int grid_width = game->window_setting->grid_width;
    int grid_height = game->window_setting->grid_width;
    while (flag && count < max_tries)
    {
        flag = false;
        rabbit->position =
            Game_CalculatePosition
            (
                game,
                GetRandomValue(0, (grid_width * grid_height) - 1)
            );

        for (int i = 0; i < snake->length; i++)
        {
            if 
            (
                rabbit->position.x == snake->body[i].x &&
                rabbit->position.y == snake->body[i].y
            )
            {
                flag = true;
                break;
            }   
        }
        count++;
    }
}

void Rabbit_Move(Game* game)
{
    Snake* snake = game->snake;
    Rabbit* rabbit = game->rabbit;
    int grid_width = game->window_setting->grid_width;
    int grid_height = game->window_setting->grid_height;
    int max_tries = 50;
    bool flag = true;
    int count = 0;
    while (flag && count < max_tries)
    {
        int dx = GetRandomValue(-1, 1);
        int dy = GetRandomValue(-1, 1);
        flag = false;
        rabbit->position.x = GameMath_Mod((int) (rabbit->position.x + dx), grid_width);
        rabbit->position.y = GameMath_Mod((int) (rabbit->position.y + dy), grid_height);
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