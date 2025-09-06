#include "snake.h"
#include "game.h"
#include "game_math.h"
#include "raylib.h"

void Snake_Init(Game* game)
{
    Vector2 v_body[game->window_setting->grid_width * game->window_setting->grid_height];
    Snake* snake = game->snake;
    snake->body = v_body;
    snake->body[0].x = 10;
    snake->body[0].y = game->window_setting->grid_height / 2;
    snake->length = INIT_SNAKE_SIZE;
    snake->dir = EAST;
}

void Snake_BindTexture(Game* game, Texture texture)
{
    game->snake->texture = texture;
}

void Snake_Move(Game* game)
{
    Snake* snake = game->snake;
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }

    int grid_width = game->window_setting->grid_width;
    int grid_height = game->window_setting->grid_height;

    switch (snake->dir) {
        case NORTH:
            snake->body[0].y = GameMath_Mod((int)(snake->body[0].y - 1.0f), grid_height);
            break;
        case SOUTH:
            snake->body[0].y = GameMath_Mod((int)(snake->body[0].y + 1.0f), grid_height);
            break;
        case WEST:
            snake->body[0].x = GameMath_Mod((int)(snake->body[0].x - 1.0f), grid_width);
            break;
        case EAST:
            snake->body[0].x = GameMath_Mod((int)(snake->body[0].x + 1.0f), grid_width);
            break;
    }
}

void Snake_SetDirection(Game* game, Direction direction)
{
    Snake* snake = game->snake;
    if 
    (
        (snake->dir == NORTH && direction == SOUTH)
        || (snake->dir == SOUTH && direction == NORTH)
        || (snake->dir == WEST && direction == EAST)
        || (snake->dir == EAST && direction == WEST)
    ) {
        return;
    }
    snake->dir = direction;
}

bool Snake_HasCollided(Game* game)
{
    Snake* snake = game->snake;
    Vector2 head = snake->body[0];

    if (snake->length > 4)
    {
        for (int i = 1; i < snake->length; i++)
        {
            if ((head.x == snake->body[i].x) && (head.y == snake->body[i].y))
            {
                return true;
            }
        }
    }  
    return false;
}

void Snake_EatsRabbit(Game* game)
{
    game->snake->length += 1;
}

void Snake_Render(Game* game)
{
    Snake* snake = game->snake;
    DrawTexture
    (
        snake->texture,
        game->window_setting->tile_size * snake->body[0].x,
        game->window_setting->tile_size * snake->body[0].y,
        GOLD
    );
    for (int i = 1; i < snake->length; i++)
    {
        DrawTexture
        (
            snake->texture,
            game->window_setting->tile_size * snake->body[i].x,
            game->window_setting->tile_size * snake->body[i].y,
            VIOLET
        );
    }
}