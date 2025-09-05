#include "snake.h"
#include "game.h"
#include "game_math.h"

void Snake_Init(Snake* snake)
{
    snake->body[0].x = 10;
    snake->body[0].y = GRID_HEIGHT / 2;
    snake->length = INIT_SNAKE_SIZE;
    snake->dir = EAST;
}

void Snake_BindTexture(Snake* snake, Texture texture)
{
    snake->texture = texture;
}

void Snake_Move(Snake* snake)
{
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->dir) {
        case NORTH:
            snake->body[0].y = GameMath_Mod((int)(snake->body[0].y - 1.0f), GRID_HEIGHT);
            break;
        case SOUTH:
            snake->body[0].y = GameMath_Mod((int)(snake->body[0].y + 1.0f), GRID_HEIGHT);
            break;
        case WEST:
            snake->body[0].x = GameMath_Mod((int)(snake->body[0].x - 1.0f), GRID_WIDTH);
            break;
        case EAST:
            snake->body[0].x = GameMath_Mod((int)(snake->body[0].x + 1.0f), GRID_WIDTH);
            break;
    }
}

void Snake_SetDirection(Snake* snake, Direction direction)
{
    if (
        (snake->dir == NORTH && direction == SOUTH)
        || (snake->dir == SOUTH && direction == NORTH)
        || (snake->dir == WEST && direction == EAST)
        || (snake->dir == EAST && direction == WEST)
    ) {
        return;
    }
    snake->dir = direction;
}

bool Snake_HasCollided(Snake* snake)
{
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

void Snake_EatsRabbit(Snake* snake)
{
    snake->length += 1;
}

void Snake_Render(Snake* snake)
{
    DrawTexture(snake->texture, TILE_SIZE * snake->body[0].x, TILE_SIZE * snake->body[0].y, GOLD);
    for (int i = 1; i < snake->length; i++)
    {
        DrawTexture(snake->texture, TILE_SIZE * snake->body[i].x, TILE_SIZE * snake->body[i].y, VIOLET);
    }
}